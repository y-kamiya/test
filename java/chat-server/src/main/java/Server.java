import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ArrayBlockingQueue;

public class Server {

    private final int MAX_CLIENT_NUM = 2;
    private final int MAX_QUEUE_SIZE = 1000;

    private int port;
    private ServerState serverState;

    public Server(int port) {
        this.port = port;
    }

    public void start() throws IOException {
        ExecutorService exec = Executors.newFixedThreadPool(MAX_CLIENT_NUM * 2);
        ServerSocket server = new ServerSocket(this.port);
        try {
			while (true) {
				System.out.println("wait accept");
				Socket socket = server.accept();
				ArrayBlockingQueue<Command> queue = new ArrayBlockingQueue<Command>(MAX_QUEUE_SIZE);
				exec.submit(new ReceiverRunnable(socket, serverState, queue));
				exec.submit(new ServerRunnable(socket, serverState, queue));
			}
        } finally {
        	server.close();
        }
    }
}
