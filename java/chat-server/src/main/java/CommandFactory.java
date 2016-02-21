import java.io.BufferedReader;
import java.io.IOException;
import java.net.Socket;

public class CommandFactory {

    private static final String COMMAND_QUIT = ":q";

    public static Command create(String name, String input) throws IOException {
        return CommandFactory.createCommand(name, input);
    }

    private static Command createCommand(String name, String input) {
        String[] inputs = input.split("\\s+", 0);
        if (inputs[0].equals(COMMAND_QUIT)) {
            return new CommandQuit(name);
        } else {
            return new CommandOther(name, inputs[0]);
        }
    }


}

