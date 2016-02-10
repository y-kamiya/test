import java.io.IOException;
import java.net.Socket;

public class CommandChangeFactor extends Command {

    private String newFactor;

    public CommandChangeFactor(String newFactor) {
    	this.newFactor = newFactor;
    }

	@Override
	public void execute(ServerState serverState, Socket socket) throws IOException {
		try {
			int factor = Integer.parseInt(newFactor);
			serverState.setFactor(factor);
		} catch (NumberFormatException e) {
			IOUtil.writeln(socket, "new factor must be int");
		}
	}
}


