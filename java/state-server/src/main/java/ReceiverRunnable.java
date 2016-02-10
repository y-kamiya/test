import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.ArrayBlockingQueue;

public class ReceiverRunnable implements Runnable {

    private Socket socket;
    private ArrayBlockingQueue<Command> queue;

    public ReceiverRunnable(Socket socket, ArrayBlockingQueue<Command> queue) {
        this.socket = socket;
        this.queue = queue;
    }

    public void run() {
        while (true) {
        	try {
				Command command = CommandFactory.create(socket);
				queue.add(command);
				if (command.getIsEnd()) {
					break;
				}
        	} catch (IOException e) {
        		continue;
        	}
        }
    }

}


