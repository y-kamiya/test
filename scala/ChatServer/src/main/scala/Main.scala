package ChatServer

import akka.actor.{ ActorSystem, Props }

object Main {
  def main(args: Array[String]) {
    val system = ActorSystem("ChatServer")
    val serverActor = system.actorOf(Props[Server], name = "server")
  }
}
