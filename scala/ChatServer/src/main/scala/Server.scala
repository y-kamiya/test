package ChatServer

import akka.actor.{ Actor, ActorRef, ActorPath, Props }
import akka.io.{ IO, Tcp }
import akka.util.ByteString
import java.net.InetSocketAddress
import scala.collection.mutable.ListBuffer

class ServerState {
  var clientList = new ListBuffer[ActorPath]

  def addClient(actorPath: ActorPath) {
    clientList += actorPath
  }

  def removeClient(actorPath: ActorPath) {
  }
}

class Server extends Actor {
  import Tcp._
  import context.system

  IO(Tcp) ! Bind(self, new InetSocketAddress("localhost", 8011))
  var serverState = new ServerState

  def receive = {
    case b @ Bound(localAddress) =>
      println(s"start listening port ${localAddress.getPort()}")
    case CommandFailed(command: Bind) =>
      println(command.failureMessage)
    case c @ Connected(remote, local) =>
      val handler = context.actorOf(Props(classOf[ChatHandler], serverState.clientList.toList))
      println(remote)
      println(local)
      println(c)
      serverState.addClient(handler.path)
      sender() ! Register(handler)

  }
}

// class NotifyingServer extends Actor {
//   var serverState: ServerState = new ServerState
//
//   def receive = {
//     case AddClient(path: ActorPath) =>
//     case RemoveClient(path: ActorPath) =>
//   }
// }

