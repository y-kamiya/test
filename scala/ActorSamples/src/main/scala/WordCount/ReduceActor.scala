package WordCount

import akka.actor.Actor
import scala.collection.mutable.ListBuffer

class ReduceActor extends Actor {
  def receive = {
    case input:ReduceInput => sender ! map(input)
    case _ => println("ReduceActor: ???")
  }

  def map(i: ReduceInput) = {
    ReduceOutput(i.key, i.entries.foldLeft(0)(_ + _._2))
  }
}

