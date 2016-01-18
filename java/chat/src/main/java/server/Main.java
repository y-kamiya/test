package server;

public class Main {

    public static void main(String[] args) throws Exception {
        System.out.println("start server");

        int port = Integer.parseInt(args[0]);
        Echo echo = new Echo(port);
        echo.start();
    }
}
