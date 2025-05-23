import java.net.Socket;
import java.util.concurrent.ArrayBlockingQueue;

public class ClientState {

    public String name;
    public Socket socket;
    public ArrayBlockingQueue<Message> queue;
    public boolean isKicked;

    public ClientState(String name, Socket socket, ArrayBlockingQueue<Message> queue) {
        this.name = name;
        this.socket = socket;
        this.queue = queue;
        this.isKicked = false;
    }

    public void sendMessage(Message message) {
        queue.add(message);
    }
}

