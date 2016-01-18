package http;

import static http.Constant.*;

import java.util.Objects;

public class Main {

    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.out.println("you need only 1 argument, pass port number you want to use");
            System.exit(1);
        }
        System.out.println("start >>>");

        HttpServer server = new HttpServer(Integer.parseInt(args[0]));
        server.start();
    }
}
