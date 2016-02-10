import java.io.BufferedReader;
import java.io.IOException;
import java.net.Socket;

public class CommandFactory {

    private static final String COMMAND_QUIT = ":q";
	private static final String COMMAND_CHANGE = ":c";

	public static Command create(Socket socket) throws IOException {
    	BufferedReader br = IOUtil.getBufferedReader(socket);
    	String input = br.readLine();
    	return CommandFactory.createCommand(input);
    }
    
    private static Command createCommand(String input) {
    	String[] inputs = input.split("\\s+", 0);
    	if (inputs[0].equals(COMMAND_QUIT)) {
    	    return new CommandQuit();
    	} else if (inputs[0].equals(COMMAND_CHANGE)) {
    	    return new CommandChangeFactor(inputs[1]);
    	} else {
    	    return new CommandOther(inputs[0]);
    	}
    }
    	
    	
}

