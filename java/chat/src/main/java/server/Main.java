package server;

public class Main {

    public static void main(String[] args) throws Exception {
        System.out.println("start server");

        int port = Integer.parseInt(args[0]);
        String type = args[1];

        Acceptor acceptor  = new Acceptor(port, type);
        acceptor.start();
    }
}
