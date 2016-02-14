import java.io.IOException;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.net.Socket;
import java.util.concurrent.ArrayBlockingQueue;

public class ReceiverRunnable implements Runnable {

    private Socket socket;
    private ServerState serverState;
    private ArrayBlockingQueue<Command> queue;

    public ReceiverRunnable(Socket socket, ServerState serverState, ArrayBlockingQueue<Command> queue) {
        this.socket = socket;
        this.serverState = serverState;
        this.queue = queue;
    }

    public void run() {
        String clientName;
    	try {
            clientName = this.readName();
    	} catch (IOException e) {
    		return;
    	}
    	this.addClient(clientName);
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
    
    private String readName() throws IOException {
    	IOUtil.writeln(socket, "What is your name?");
    	String name = IOUtil.readLine(socket);
    	if (!serverState.isNameDuplicate(name)) {
    		return name;
    	}
    	return this.readName();
    }

    private void addClient(String name) {
    	ClientState clientState = new ClientState(name, socket);
    	serverState.addClient(name, clientState);
    }

}


