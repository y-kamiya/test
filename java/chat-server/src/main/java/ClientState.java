import java.net.Socket;
import java.util.concurrent.ArrayBlockingQueue;

public class ClientState {

	private static final int QUEUE_MAX_SIZE = 1000;

	public String name;
	public Socket socket;
	public ArrayBlockingQueue<Command> queue;
	public boolean isKicked;
	
	public ClientState(String name, Socket socket) {
		this.name = name;
		this.socket = socket;
		this.queue = new ArrayBlockingQueue<Command>(QUEUE_MAX_SIZE);
		this.isKicked = false;
	}
}

