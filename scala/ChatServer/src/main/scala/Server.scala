package ChatServer

import akka.actor.{ Actor, ActorRef, ActorPath, Props }
import akka.io.{ IO, Tcp }
import akka.util.ByteString
import java.net.InetSocketAddress
import scala.collection.mutable.ListBuffer

class Server extends Actor {
  import Tcp._
  import context.system

  IO(Tcp) ! Bind(self, new InetSocketAddress("localhost", 8011))

  def receive = {
    case b @ Bound(localAddress) =>
      println(s"start listening port ${localAddress.getPort()}")
    case CommandFailed(command: Bind) =>
      println(command.failureMessage)
    case c @ Connected(remote, local) =>
      val handler = context.actorOf(Props(classOf[ChatHandler], sender()))
      sender() ! Register(handler)
  }
}
