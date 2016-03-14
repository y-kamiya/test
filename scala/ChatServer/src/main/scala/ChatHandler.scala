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
      // var a = context.actorSelection(path)
      println(list)
      context.actorSelection("/user/server/*") ! "Message 1"
      list.foreach(path => {
        println(path)
      })
    case PeerClosed => context.stop(self)
    case m:String => println(m)
  }
}


