import java.net.Socket;

public class CommandQuit extends Command {

    public boolean isEnd = true;

	@Override
	public boolean getIsEnd() {
		return isEnd;
	}

	@Override
    public void execute(ServerState serverState, Socket socket) {
        // noop
    }
}

