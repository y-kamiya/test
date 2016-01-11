package http;

import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {

    public static void main(String[] args) throws Exception {
        System.out.println("start >>>");

        try {
            ServerSocket server = new ServerSocket(8011);
            Socket socket = server.accept();
            InputStream in = socket.getInputStream();

            HttpRequest request = new HttpRequest(in);

            System.out.println(request.getHeaderText());
            System.out.println(request.getBodyText());

        } catch (Exception e) {
            System.out.println("error!");
            System.out.println(e);
        }
        System.out.println("<<< end");
    }
}
