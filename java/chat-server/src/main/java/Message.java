import java.io.IOException;
import java.net.Socket;

abstract public class Message {

    boolean isEnd = false;

    String from;
    String message;

    public Message(String from, String message) {
        this.from = from;
        this.message = message;
    }

    public boolean getIsEnd() {
        return isEnd;
    }

    abstract public void execute(Socket socket) throws IOException;
}
