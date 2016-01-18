package server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Echo {

    private final String CRLF = "\r\n";
    private final String COMMAND_QUIT = ":q";

    private int port;

    public Echo(int port) {
        this.port = port;
    }

    public void start() throws IOException {
        ServerSocket server = new ServerSocket(this.port);
        while (true) {
            System.out.println("wait accept");
            Socket socket = server.accept();
            this.run(socket);
        }
    }

    private void run(Socket socket) throws IOException {
        try {
            InputStream in = socket.getInputStream();
            OutputStream out = socket.getOutputStream();

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
            socket.close();

        } catch (Exception e) {
            System.out.println("error!");
            System.out.println(e);
        }
    }
}
