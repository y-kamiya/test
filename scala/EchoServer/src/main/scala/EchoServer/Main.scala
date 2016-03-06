package EchoServer

object Main {
  def main(args: Array[String]) : Unit = {
    val port = getPort(args(0))
    val server = new Server(port)
    server.start()
  }

  def getPort(s: String): Int = {
    val option = toInt(s)
    if (option.isEmpty) {
      println("must pass port number to listen")
      exit(1)
    }
    option.get
  }

  def toInt(s: String): Option[Int] = {
    try {
      Some(s.toInt)
    } catch {
      case e: Exception => None
    }
  }
}
