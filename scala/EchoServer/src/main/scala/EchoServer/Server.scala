package EchoServer

import scala.io.Source
import java.nio.charset.StandardCharsets
import java.io.{BufferedReader, BufferedWriter, InputStreamReader, OutputStreamWriter}
import java.net.{Socket, ServerSocket}
import java.util.concurrent.{Executors, ExecutorService}

class Server(val port: Int) {

  final val MAX_THREAD_NUM = 2

  def start() {
    val exec = Executors.newFixedThreadPool(MAX_THREAD_NUM);
    val server = new ServerSocket(port);
    try {
      println(s"wait accept on port: $port")
      Iterator
        .continually(server.accept)
        .foreach { socket =>
          exec.submit(new EchoRunnable(socket))
        }
    } finally {
      exec.shutdown()
    }
  }
}

class EchoRunnable(socket: Socket) extends Runnable {

  final val CommandQuit = ":q"
  final val Crlf = "\r\n"

  def run {
    val br = new BufferedReader(new InputStreamReader(socket.getInputStream, StandardCharsets.UTF_8))
    val bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream, StandardCharsets.UTF_8))
    println("wait input")
    try {
      Iterator
        .continually(br.readLine)
        .takeWhile(str => str != CommandQuit)
        .withFilter(!_.isEmpty)
        .foreach { str =>
          bw.write(str + Crlf)
          bw.flush
        }
    } finally {
      socket.close
    }
  }
}
