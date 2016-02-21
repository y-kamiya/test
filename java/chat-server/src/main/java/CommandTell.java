import java.net.Socket;

public class CommandTell extends Command {

    public String from;
    public String to;
    public String msg;

    public CommandTell(String from, String to, String msg) {
        this.from = from;
        this.to = to;
        this.msg = msg;
    }

    @Override
    public void execute(ServerState serverState, Socket socket) {
        serverState.tell(to, new MessageTell(from, msg));
    }
}

