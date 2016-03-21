package ChatServer

import akka.actor.{ Actor, ActorRef, ActorPath, Props, ReceiveTimeout, PoisonPill }
import akka.io.{ IO, Tcp }
import akka.util.ByteString
import java.net.InetSocketAddress
import scala.collection.mutable.HashMap
import scala.concurrent.duration._

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

  def size: Int = {
    return map.size
  }

  def update(name: String, path: ActorPath) {
    map(name) = path
  }

  def contains(name: String): Boolean = {
    return map.contains(name)
  }

}

trait ChatMessage
case class NewClient(name: String) extends ChatMessage
case class AckNewClient(name: String) extends ChatMessage
case class RemoveClient(name: String) extends ChatMessage
case class Broadcast(name: String, msg: String) extends ChatMessage
case class Tell(name: String, msg: String) extends ChatMessage
case class NameConfirmation(name: String) extends ChatMessage
case class AckNameConfirmation(name: String, isOk: Boolean) extends ChatMessage

class ChatHandler(ref: ActorRef, memberCount: Int) extends Actor {
  import Tcp._

  val Crlf = "\r\n"
  val Separator = " "

  var clientName = "undefined"
  var clientMap = new ClientMap

  respondToClient(s"What your name?$Crlf")

  def receive = {
    case Received(name) =>
      println("receive name")
      clientName = name.utf8String.stripLineEnd
      clientMap.add(clientName, sender().path)
      memberCount match {
        case 0 => context.become(loggedIn)
        case _ => 
          notifyAll(NameConfirmation(clientName))
          context.setReceiveTimeout(10 seconds)
          context.become(naming)
      }
  }

  def naming: Receive = {
    case AckNameConfirmation(name, true) =>
      println(s"success $clientName")
      clientMap.add(name, sender().path)
      if (memberCount / 2 < clientMap.size) {
        context.setReceiveTimeout(Duration.Undefined)
        notifyJoin(clientName)
        context.become(loggedIn)
      }
    case AckNameConfirmation(_, false) => failedToNameDecision
    case ReceiveTimeout => failedToNameDecision
  }

  def failedToNameDecision {
    println(s"failed $clientName")
    context.setReceiveTimeout(Duration.Undefined)
    respondToClient(s"$clientName has already used$Crlf")
    self ! PoisonPill
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
    case NameConfirmation(name) if sender == self => noop
    case NameConfirmation(name) =>
      println(s"NameConfirmation in $clientName")
      val exist = clientMap.contains(name)
      sender() ! AckNameConfirmation(clientName, !exist)
      if (!exist) {
        clientMap.add(name, sender().path)
      }

    case Broadcast(name, str) =>
      println("receive Broadcast")
      respondToClient(s"* $name *: $str$Crlf")
    case NewClient(name) =>
      clientMap.update(name, sender().path)
      if (name != clientName) {
        sender() ! AckNewClient(clientName)
        respondToClient(s"greet from $name$Crlf")
      }
    case AckNewClient(name) =>
      clientMap.add(name, sender().path)
      respondToClient(s"greet from $name$Crlf")
    case Tell(name, str) =>
      println("receive Tell")
      respondToClient(s"** $name **: $str$Crlf")
    case RemoveClient(name) if sender == self =>
      println("receive RemoveClient to me")
      context.stop(self)
    case RemoveClient(name) =>
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

  def notice(str: String) = respondToClient(s"<notice> $str$Crlf")

  def info(str: String) = println(str)
}


