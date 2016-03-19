package ChatServer

import akka.actor.{ Actor, ActorRef, ActorPath, Props }
import akka.io.{ IO, Tcp }
import akka.util.ByteString
import java.net.InetSocketAddress
import scala.collection.mutable.HashMap

class ClientMap {
  val map: HashMap[String, ActorPath] = new HashMap

  def get(name: String): Option[ActorPath] = {
    return map.get(name)
  }

  def add(name: String, path: ActorPath) {
    map += (name -> path)
  }

  def remove(name: String) {
    map -= name
  }
}

trait ChatMessage
case class NewClient(name: String) extends ChatMessage
case class AckNewClient(name: String) extends ChatMessage
case class Broadcast(name: String, msg: String) extends ChatMessage
case class Tell(name: String, msg: String) extends ChatMessage
case class Notice(msg: String) extends ChatMessage

class ChatHandler(ref: ActorRef) extends Actor {
  import Tcp._

  val Crlf = "\r\n"
  val Separator = " "

  var clientName: String = "undefined"
  val clientMap = new ClientMap

  confirmName

  def confirmName = {
    ref ! Write(ByteString(s"What your name?$Crlf"))
  }

  def receive = {
    case Received(name) =>
      println("receive name")
      clientName = name.utf8String.stripLineEnd
      clientMap.add(clientName, sender().path)
      notifyJoin(clientName)
      context.become(loggedIn)
  }

  def loggedIn: Receive = {
    case Received(data) =>
      println("receive message")
      val str = data.decodeString("UTF-8").init
      val commands = str.split(Separator).toList
      commands match {
        case ":t" :: name :: list if !list.isEmpty =>
          tell(name, list.mkString(Separator))
        case ":t" :: name :: list => noop
        case List(c, _*) if c.startsWith(":") =>
          notice(s"unknown command $c$Crlf")
        case List("") => noop
        case _ => 
          broadcast(clientName, str)
      }
      // commands(0) match {
      //   case ":t" => tell(commands(1), commands(2))
      //   case c if c.startsWith(":") => notice(s"unknown command $c$Crlf")
      //   case _ => broadcast(clientName, str)
      // }
    case PeerClosed => context.stop(self)
    case Broadcast(name, str) =>
      println("receive Broadcast")
      ref ! Write(ByteString(s"* $name *: $str$Crlf"))
    case NewClient(name) =>
      clientMap.add(name, sender().path)
      if (name != clientName) {
        sender() ! AckNewClient(clientName)
        ref ! Write(ByteString(s"greet from $name$Crlf"))
      }
    case AckNewClient(name) =>
      clientMap.add(name, sender().path)
      ref ! Write(ByteString(s"greet from $name$Crlf"))
    case Tell(name, str) =>
      println("receive Tell")
      respondToClient(s"** $name **: $str$Crlf")
    case Notice(str) =>
      println("receive Notice")
      respondToClient(s"<notice> $str$Crlf")
  }

  def noop() {
  }

  def respondToClient(str: String) {
    ref ! Write(ByteString(str))
  }

  def notifyJoin(name: String) {
    nofifyAll(name, NewClient(name))
  }

  def broadcast(name: String, str: String) {
    nofifyAll(name, Broadcast(name, str))
  }

  def nofifyAll(name: String, message: ChatMessage) {
    context.actorSelection("/user/server/*") ! message
  }

  def tell(name: String, str: String) {
    clientMap.get(name) match {
      case Some(path) => context.actorSelection(path) ! Tell(clientName, str)
      case None => notice(s"$name does not exist$Crlf")
    }
  }

  def notice(str: String) {
    self ! Notice(str)
  }
}


