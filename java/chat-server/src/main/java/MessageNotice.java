
import java.io.IOException;
import java.net.Socket;

public class MessageNotice extends Message {

    public MessageNotice(String message) {
        super("system", message);
    }

    @Override
    public void execute(Socket socket) throws IOException {
        IOUtil.writeln(socket, "*** " + message);
    }
}
