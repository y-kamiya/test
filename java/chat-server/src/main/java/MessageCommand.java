
import java.io.IOException;
import java.net.Socket;

public class MessageCommand extends Message {

    Command command;
    ServerState serverState;

    public MessageCommand(String from, String message, ServerState serverState) throws IOException {
        super(from, message);
        this.serverState = serverState;
        this.command = this.parseInput();
    }

    @Override
    public boolean getIsEnd() {
        return command.getIsEnd();
    }

    @Override
    public void execute(Socket socket) throws IOException {
        command.execute(serverState, socket);
    }

    private Command parseInput() throws IOException {
        return CommandFactory.create(from, message);
    }
}
