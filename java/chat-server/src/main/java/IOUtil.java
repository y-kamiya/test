import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class IOUtil {
    
    public static final String CRLF = "\r\n";

    public static BufferedReader getBufferedReader(Socket socket) throws IOException {
        InputStream in = socket.getInputStream();
        return new BufferedReader(new InputStreamReader(in, StandardCharsets.UTF_8));
    }

    public static BufferedWriter getBufferedWriter(Socket socket) throws IOException {
        OutputStream out = socket.getOutputStream();
        return new BufferedWriter(new OutputStreamWriter(out, StandardCharsets.UTF_8));
    }
    
    public static void write(Socket socket, String message) throws IOException {
    	BufferedWriter bw = IOUtil.getBufferedWriter(socket);
    	bw.write(message);
    	bw.flush();
    }

    public static void writeln(Socket socket, String message) throws IOException {
    	IOUtil.write(socket, message + CRLF);
    }

    public static String readLine(Socket socket) throws IOException {
    	return IOUtil.getBufferedReader(socket).readLine();
    }
}
