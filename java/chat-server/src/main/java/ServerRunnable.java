import java.net.Socket;
import java.util.Objects;
import java.util.concurrent.ArrayBlockingQueue;

public class ServerRunnable implements Runnable {

    private Socket socket;
    private ServerState serverState;
    private ArrayBlockingQueue<Message> queue;

    public ServerRunnable(Socket socket, ServerState serverState, ArrayBlockingQueue<Message> queue) {
        this.socket = socket;
        this.serverState = serverState;
        this.queue = queue;
    }

    public void run() {
        Objects.requireNonNull(this.socket);

        try {
            while (true) {
                Message message = this.queue.take();
                message.execute(socket);
                if (message.getIsEnd()) {
                    break;
                }
            }
            this.socket.close();

        } catch (Exception e) {
            System.out.println("error!");
            System.out.println(e);
        }
    }

}


