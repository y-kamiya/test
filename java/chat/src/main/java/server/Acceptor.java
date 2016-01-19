package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Acceptor {

    private final int MAX_THREAD_NUM = 2;

    private int port;
    private String type;

    public Acceptor(int port, String type) {
        this.port = port;
        this.type = type;
    }

    public void start() throws IOException {
        ExecutorService exec = Executors.newFixedThreadPool(MAX_THREAD_NUM);
        ServerSocket server = new ServerSocket(this.port);
        while (true) {
            System.out.println("wait accept");
            Socket socket = server.accept();
            Runnable runnable = this.getRunnable(type, socket);
            exec.submit(runnable);
        }
    }

    private Runnable getRunnable(String type, Socket socket) {
        switch (type) {
            case "echo": return new EchoRunnable(socket);
            case "chat": return new ChatRunnable(socket);
            default: return new NoopRunnable();
        }
    }

}
