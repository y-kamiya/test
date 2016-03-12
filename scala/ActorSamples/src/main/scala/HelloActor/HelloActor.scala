package HelloActor

import akka.actor.Actor
import akka.actor.ActorSystem
import akka.actor.Props

case class End()

object Main {
  def main(args: Array[String]) {
    val system = ActorSystem("HelloSystem")
    val helloActor = system.actorOf(Props(new HelloActor("test")), name = "helloActor")
    helloActor ! "hello"
    helloActor ! "hoge"
    helloActor ! End
  }
}

class HelloActor(arg: String) extends Actor {
  def receive = {
    case m:String => println("message: " + arg + m)
    case End => println("End."); System.exit(0)
  }
}
