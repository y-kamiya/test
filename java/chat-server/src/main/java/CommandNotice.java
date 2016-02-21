import java.net.Socket;

public class CommandNotice extends Command {

    public String to;
    public String msg;

    public CommandNotice(String to, String msg) {
        this.to = to;
        this.msg = msg;
    }

    @Override
    public void execute(ServerState serverState, Socket socket) {
        serverState.tell(to, new MessageNotice(msg));
    }
}

