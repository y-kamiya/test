import java.io.IOException;
import java.net.Socket;

public class CommandOther extends Command {

	private String input;
	
	public CommandOther(String input) {
		this.input = input;
	}

	@Override
    public void execute(ServerState serverState, Socket socket) throws IOException {
    	try {
    		IOUtil.writeln(socket, input);
    	} catch (NumberFormatException e) {
    		IOUtil.writeln(socket, "input must be int");
    	}
    }
}

