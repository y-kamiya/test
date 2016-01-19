import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server {

    private final int MAX_THREAD_NUM = 2;

    private int port;

    public Server(int port) {
        this.port = port;
    }

    public void start() throws IOException {
        ExecutorService exec = Executors.newFixedThreadPool(MAX_THREAD_NUM);
        ServerSocket server = new ServerSocket(this.port);
        while (true) {
            System.out.println("wait accept");
            Socket socket = server.accept();
            exec.submit(new EchoRunnable(socket));
        }
    }
}
