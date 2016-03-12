package EchoServer

import akka.actor.{ Actor, ActorRef, Props }
import akka.io.{ IO, Tcp }
import akka.util.ByteString
import java.net.InetSocketAddress

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
      val handler = context.actorOf(Props[EchoHandler])
      sender() ! Register(handler)

  }
}

class EchoHandler extends Actor {
  import Tcp._
  def receive = {
    case Received(data) => sender() ! Write(data)
    case PeerClosed => context.stop(self)
  }
}

