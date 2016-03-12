package WordCount

import akka.actor.Actor
import scala.collection.mutable.ListBuffer

class MapActor extends Actor {
  def receive = {
    case text:String => sender() ! map(text)
    case _ => println("MapActor: ???")
  }

  def map(text: String) = {
    val words = new ListBuffer[(String, Int)]
    text.split(' ').foreach(words += _->1)
    MapOutput(words.toList)
  }
}
