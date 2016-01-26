import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.net.Socket;
import java.util.Objects;
import java.util.UUID;
import java.util.Iterator;

public class FactorRunnable implements Runnable {

    private final String CRLF = "\r\n";
    private final String COMMAND_QUIT = ":q";
    private final String COMMAND_CHANGE = ":c";

    private Socket socket;
    private ServerState serverState;
    private String id;

    public FactorRunnable(Socket socket, ServerState serverState) {
        this.socket = socket;
        this.serverState = serverState;
        this.id = this.generateId();
    }

    public void run() {
        Objects.requireNonNull(this.socket);

        try {
            BufferedReader br = this.getBufferedReader();
            BufferedWriter bw = this.getBufferedWriter();

            this.serverState.addClient(this.id, bw);

            while (true) {
                System.out.println("wait input");
                String input = br.readLine();
                boolean isEnd = this.parseInput(input);
                if (isEnd) {
                    break;
                }
                bw.write(CRLF);
                bw.flush();
            }
            this.serverState.removeClient(this.id);
            this.socket.close();

        } catch (Exception e) {
            System.out.println("error!");
            System.out.println(e);
        }
    }

    private boolean parseInput(String input) throws IOException {
        String[] inputs = input.split("\\s+", 0);
        if (inputs[0].equals(COMMAND_QUIT)) {
            return true;
        } else if (inputs[0].equals(COMMAND_CHANGE)) {
            int factor = Integer.parseInt(inputs[1]);
            this.serverState.setFactor(factor);
            Iterator<BufferedWriter> it = this.serverState.getAllClient().iterator();
            while (it.hasNext()) {
                it.next().write("change factor to " + factor);
            }
        } else {
            BufferedWriter bw = this.serverState.getClientById(this.id);
            String output = "";
            try {
                int in = Integer.parseInt(inputs[0]) * this.serverState.getFactor();
                output = String.valueOf(in);
            } catch (NumberFormatException e) {
                output = "cannot parse to int";
            }
            bw.write(output);
        }
        return false;
    }

    private String generateId() {
        return UUID.randomUUID().toString();
    }

    private BufferedReader getBufferedReader() throws IOException {
        InputStream in = this.socket.getInputStream();
        return new BufferedReader(new InputStreamReader(in, "UTF-8"));
    }

    private BufferedWriter getBufferedWriter() throws IOException {
        OutputStream out = this.socket.getOutputStream();
        return new BufferedWriter(new OutputStreamWriter(out, "UTF-8"));
    }

}


