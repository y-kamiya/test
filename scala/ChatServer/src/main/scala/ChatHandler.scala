package ChatServer

import akka.actor.{ Actor, ActorRef, ActorPath, Props }
import akka.io.{ IO, Tcp }
import akka.util.ByteString
import java.net.InetSocketAddress

class ChatHandler(list: List[ActorPath]) extends Actor {
  import Tcp._
  def receive = {
    case Received(data) => 
      sender() ! Write(data)
      list.foreach(path => {
        context.actorSelection(path) ! "Message 1"
      })
    case PeerClosed => context.stop(self)
  }
}


