import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.ArrayBlockingQueue;

public class ReceiverRunnable implements Runnable {

    private Socket socket;
    private ServerState serverState;
    private ArrayBlockingQueue<Message> queue;

    public ReceiverRunnable(Socket socket, ServerState serverState, ArrayBlockingQueue<Message> queue) {
        this.socket = socket;
        this.serverState = serverState;
        this.queue = queue;
    }

    public void run() {
        String clientName;
        try {
            clientName = this.readName();
            this.addClient(clientName);
        } catch (IOException e) {
            System.out.println("IOException in readName(): " + e);
            return;
        }
        while (true) {
            try {
                String input = IOUtil.readLine(socket);
                Message message = new MessageCommand(clientName, input, serverState);
                queue.add(message);
                if (message.getIsEnd()) {
                    break;
                }
            } catch (IOException e) {
                continue;
            }
        }
        this.removeClient(clientName);
    }

    private void removeClient(String name) {
        serverState.removeClient(name);
    }

    private String readName() throws IOException {
        IOUtil.writeln(socket, "What is your name?");
        String name = IOUtil.readLine(socket);
        System.out.println("client name: " + name);
        if (!serverState.isNameDuplicate(name)) {
            return name;
        }
        return this.readName();
    }

    private void addClient(String name) throws IOException {
        ClientState clientState = new ClientState(name, socket, queue);
        serverState.addClient(name, clientState);
        IOUtil.writeln(socket, "Hi, " + name);
    }

}


