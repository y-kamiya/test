package ChatServer

import akka.actor.{ Actor, ActorRef, ActorPath, Props }
import akka.io.{ IO, Tcp }
import akka.util.ByteString
import java.net.InetSocketAddress
import scala.collection.mutable.HashMap

class ClientMap {
  var map: HashMap[String, ActorPath] = new HashMap

  def add(name: String, path: ActorPath) {
    map += (name -> path)
  }

  def remove(name: String) {
    map -= name
  }
}

trait ChatMessage
case class NewClient(name: String) extends ChatMessage
case class Broadcast(name: String, msg: String) extends ChatMessage
case class Tell(name: String, msg: String) extends ChatMessage

class ChatHandler(ref: ActorRef) extends Actor {
  import Tcp._

  var clientName: String = "undefined"
  val clientMap = new ClientMap

  confirmName

  def confirmName = {
    ref ! Write(ByteString("What your name?"))
  }

  def receive ={
    case name: String => 
      clientName = name
      clientMap.add(name, sender().path)
      notifyJoin(name)
      context.become(loggedIn)
  }

  def loggedIn: Receive = {
    case Received(data) => broadcast(clientName, data.decodeString("UTF-8"))
    case PeerClosed => context.stop(self)
    case Broadcast(name, str) => ref ! s"*** $name ***: $str"
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
}


