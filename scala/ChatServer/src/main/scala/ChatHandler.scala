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
case class RemoveClient(name: String) extends ChatMessage
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
      println(data)
      val str = data.utf8String.stripLineEnd
      val commands = str.split(Separator).toList
      println(commands)
      commands match {
        case List(":t", name) => noop
        case ":t" :: name :: list => tell(name, list.mkString(Separator))
        case List(":q", _*)       => kick(clientName)
        case List(":k", name, _*) => kick(name)
        case List(c, _*) if c.startsWith(":") =>
          notice(s"unknown command $c$Crlf")
        case List("") => noop
        case _ =>
          broadcast(clientName, str)
      }
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
    case RemoveClient(name) if name == clientName =>
      println("receive RemoveClient to me")
      context.stop(self)
    case RemoveClient(name) =>
      println(ByteString(name))
      println(ByteString(clientName))
      println(name == clientName)
      if (name == clientName) {
        context.stop(self)
      }
      println("receive RemoveClient")
      clientMap.remove(name)
    case m => println(s"unknown message $m")
  }

  def noop() {
  }

  def kick(name: String) {
    notifyAll(RemoveClient(name))
  }

  def respondToClient(str: String) {
    ref ! Write(ByteString(str))
  }

  def notifyJoin(name: String) {
    notifyAll(NewClient(name))
  }

  def broadcast(name: String, str: String) {
    notifyAll(Broadcast(name, str))
  }

  def notifyAll(message: ChatMessage) {
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


