public class Main {

    public static void main(String[] args) throws Exception {
        System.out.println("start server");

        int port = Integer.parseInt(args[0]);
        int initialFactor = Integer.parseInt(args[1]);

        Server acceptor  = new Server(port, initialFactor);
        acceptor.start();
    }
}
