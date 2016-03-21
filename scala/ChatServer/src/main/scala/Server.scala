package ChatServer

import akka.actor.{ Actor, ActorRef, ActorPath, Props }
import akka.io.{ IO, Tcp }
import akka.util.ByteString
import java.net.InetSocketAddress
import scala.collection.mutable.ListBuffer

class Server extends Actor {
  import Tcp._
  import context.system

  var memberCount = 0

  IO(Tcp) ! Bind(self, new InetSocketAddress("localhost", 8011))

  def receive = {
    case b @ Bound(localAddress) =>
      println(s"start listening port ${localAddress.getPort()}")
    case CommandFailed(command: Bind) =>
      println(command.failureMessage)
    case c @ Connected(remote, local) =>
      val handler = context.actorOf(Props(classOf[ChatHandler], sender(), memberCount))
      sender() ! Register(handler)
      memberCount += 1
    case RemoveClient(name) => memberCount -= 1
  }
}
