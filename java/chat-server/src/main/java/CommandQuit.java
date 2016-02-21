import java.net.Socket;

public class CommandQuit extends Command {

    public boolean isEnd = true;

    public String from;

    public CommandQuit(String from) {
        this.from = from;
    }

    @Override
    public boolean getIsEnd() {
        return isEnd;
    }

    @Override
    public void execute(ServerState serverState, Socket socket) {
        serverState.broadcast(new MessageBroadcast(from, from + " exited"));
    }
}

