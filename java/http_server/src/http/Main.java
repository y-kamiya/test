package http;

import static http.Constant.*;

import java.io.File;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {

    public static void main(String[] args) throws Exception {
        System.out.println("start >>>");

        try {
            ServerSocket server = new ServerSocket(8011);
            Socket socket = server.accept();
            InputStream in = socket.getInputStream();
            OutputStream out = socket.getOutputStream();

            HttpRequest request = new HttpRequest(in);

            System.out.println(request.getHeaderText());
            System.out.println(request.getBodyText());

            HttpResponse response = new HttpResponse(Status.OK);

            HttpHeader header = request.getHeader();
            if (header.isGetMethod()) {
                response.setBody(new File(".", header.getPath()));
            }
            response.writeTo(out);

        } catch (Exception e) {
            System.out.println("error!");
            System.out.println(e);
        }
        System.out.println("<<< end");
    }
}
