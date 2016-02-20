import java.net.Socket;
import java.util.Objects;
import java.util.concurrent.ArrayBlockingQueue;

public class ServerRunnable implements Runnable {

    private Socket socket;
    private ServerState serverState;
    private ArrayBlockingQueue<Command> queue;

    public ServerRunnable(Socket socket, ServerState serverState, ArrayBlockingQueue<Command> queue) {
        this.socket = socket;
        this.serverState = serverState;
        this.queue = queue;
    }

    public void run() {
        Objects.requireNonNull(this.socket);

        try {
            while (true) {
                Command command = this.queue.take();
                command.execute(this.serverState, socket);
                if (command.getIsEnd()) {
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


