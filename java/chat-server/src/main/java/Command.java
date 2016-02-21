import java.io.IOException;
import java.net.Socket;

abstract public class Command {

    boolean isEnd = false;

    public boolean getIsEnd() {
        return isEnd;
    }

    abstract public void execute(ServerState serverState, Socket socket) throws IOException;
}
