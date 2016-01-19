package server;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.net.Socket;
import java.util.Objects;

public class FactorRunnable implements Runnable {

    private final String CRLF = "\r\n";
    private final String COMMAND_QUIT = ":q";

    private Socket socket;

    private int factor;
    private synchronized int getFactor() { return this.factor; }
    private synchronized int setFactor(int factor) { return this.factor = factor; }

    public FactorRunnable(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        Objects.requireNonNull(this.socket);

        try {
            InputStream in = this.socket.getInputStream();
            OutputStream out = this.socket.getOutputStream();

            BufferedReader br = new BufferedReader(new InputStreamReader(in, "UTF-8"));
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(out, "UTF-8"));

            while (true) {
                System.out.println("wait input");
                String input = br.readLine();
                if (input.equals(COMMAND_QUIT)) {
                    break;
                }
                bw.write(input + CRLF);
                bw.flush();
            }
            this.socket.close();

        } catch (Exception e) {
            System.out.println("error!");
            System.out.println(e);
        }
    }
}


