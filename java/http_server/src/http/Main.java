package http;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {

    public static void main(String[] args) throws Exception {
        System.out.println("start >>>");

        try {
            ServerSocket server = new ServerSocket(8011);
            Socket socket = server.accept();
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream(), "UTF-8"));
            // in.lines().forEach(System.out::println);

            String line = in.readLine();
            StringBuilder header = new StringBuilder();

            int contentLength = 0;

            while (line != null && !line.isEmpty()) {
                if (line.startsWith("Content-Length")) {
                    contentLength = Integer.parseInt(line.split(":")[1].trim());
                }
                header.append(line + "\n");
                line = in.readLine();
            }
            String body = null;
            if (0 < contentLength) {
                char[] c = new char[contentLength];
                in.read(c);
                body = new String(c);
            }
            System.out.println(header);
            System.out.println(body);

        } catch (Exception e) {
            System.out.println("error!");
            System.out.println(e);
        }
        System.out.println("<<< end");
    }
}
