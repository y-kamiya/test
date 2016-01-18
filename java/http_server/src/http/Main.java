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

            HttpHeader header = request.getHeader();

            HttpResponse response;
            if (header.isGetMethod()) {
                File file = new File(".", header.getPath());
                if (file.exists()) {
                    response = new HttpResponse(Status.OK);
                    response.setBody(new File(".", header.getPath()));
                } else {
                    response = new HttpResponse(Status.NOT_FOUND);
                    response.setBody("file is not found");
                }
            } else {
                response = new HttpResponse(Status.OK);
                response.setBody("this is not GET request");
            }
            response.writeTo(out);

        } catch (Exception e) {
            System.out.println("error!");
            System.out.println(e);
        }
        System.out.println("<<< end");
    }
}
