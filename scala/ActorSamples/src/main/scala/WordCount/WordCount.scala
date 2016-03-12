package WordCount

import akka.actor.Actor
import akka.actor.ActorRef
import akka.actor.ActorSystem
import akka.actor.Props

case class MapOutput(val entries:List[(String, Int)])
case class ReduceInput(val key:String,
                       val entries:List[(String, Int)])

case class ReduceOutput(val key:String, val value:Int)

case class Begin()
object WordCount {

  val system = ActorSystem("WordCountSystem")

  def main(args: Array[String]) {
    val data = List("Hello World",
                    "Hello Scala World",
                    "Hello Java",
                    "Hello Java Hello")
    val mapActors = prepareMapActors(3)
    val reduceActors = prepareReduceActors(3)
    val masterActor = system.actorOf(
      Props(new MasterActor(mapActors, reduceActors, data)),
      name = s"masterActor"
    )

    masterActor ! Begin
    while (true) {
      println("WordCount: processing...")
      Thread.sleep(1000L)
    }
  }

  def prepareMapActors(num:Int): Array[ActorRef] = {
    val mapActors = new Array[ActorRef](num)
    for (i <- 0 to num-1)
      mapActors(i) = system.actorOf(Props[MapActor], name = s"mapActor${i}")
    mapActors
  }

  def prepareReduceActors(num:Int): Array[ActorRef] = {
    val reduceActors = new Array[ActorRef](num)
    for (i <- 0 to num-1)
      reduceActors(i) = system.actorOf(Props[ReduceActor], name = s"reduceActor${i}")
    reduceActors
  }
}
