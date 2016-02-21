import java.io.IOException;
import java.net.Socket;

public class CommandOther extends Command {

    private String from;
    private String input;

    public CommandOther(String from, String input) {
        this.from = from;
        this.input = input;
    }

    @Override
    public void execute(ServerState serverState, Socket socket) throws IOException {
        serverState.broadcast(new MessageBroadcast(from, input));
    }
}

