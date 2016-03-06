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
      while (true) {
        println("wait accept");
        val socket = server.accept();
        exec.submit(new EchoRunnable(socket));
      }
    } finally {
      exec.shutdown()
    }
  }
}

class EchoRunnable(socket: Socket) extends Runnable {

  final val COMMAND_QUIT = ":q"

  def run {
    val br = new BufferedReader(new InputStreamReader(socket.getInputStream, StandardCharsets.UTF_8))
    val bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream, StandardCharsets.UTF_8))
    var isContinue = true
    while (isContinue) {
      println("wait input")
      var str = br.readLine
      str match {
        case COMMAND_QUIT => bw.write("quit.\n"); isContinue = false
        case m: String => bw.write(m + "\n")
      }
      bw.flush
    }
    socket.close
  }
}
