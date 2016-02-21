
import java.io.IOException;
import java.net.Socket;

public class MessageTell extends Message {

    public MessageTell(String from, String message) {
        super(from, message);
    }

    @Override
    public void execute(Socket socket) throws IOException {
        IOUtil.writeln(socket, "*" + from + "* " + message);
    }
}
