package http;

import static http.Constant.*;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.io.OutputStream;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class IOUtil {

    private static final Charset UTF_8 = StandardCharsets.UTF_8;

    public static void println(OutputStream out, String line) {
        print(out, line + CRLF);
    }

    public static void print(OutputStream out, String line) {
        try {
            out.write(line.getBytes(UTF_8));
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    }
}

