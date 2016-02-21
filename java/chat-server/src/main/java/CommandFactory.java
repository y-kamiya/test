import java.io.IOException;

public class CommandFactory {

    private static final String COMMAND_QUIT = ":q";
    private static final String COMMAND_TELL = ":t";

    public static Command create(String from, String input) throws IOException {
        return CommandFactory.createCommand(from, input);
    }

    private static Command createCommand(String from, String input) {
        String[] inputs = input.split("\\s+", 0);
        if (inputs[0].equals(COMMAND_QUIT)) {
            return new CommandQuit(from);
        } else if (inputs[0].equals(COMMAND_TELL)) {
            if (inputs.length < 3) {
                return new CommandNotice(from, "tell command usage: ':t name message'");
            }
            return new CommandTell(from, inputs[1], inputs[2]);
        } else {
            return new CommandOther(from, inputs[0]);
        }
    }


}

