package http;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UncheckedIOException;
import java.util.stream.Stream;

public class HttpRequest {

    private final HttpHeader header;
    private final String bodyText;

    public HttpRequest(InputStream input) {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(input, "UTF-8"));
            this.header = new HttpHeader(br);
            this.bodyText = this.readBodyText(br);

        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    }

    private String readBodyText(BufferedReader br) throws IOException {
        final int contentLength = this.header.getContentLength();
        if (contentLength <= 0) {
            return null;
        }
        char[] c = new char[contentLength];
        br.read(c);
        return new String(c);
    }

    private int getContentLength() {
        return this.header.getContentLength();
    }

    public String getHeaderText() {
        return this.header.getHeaderText();
    }

    public String getBodyText() {
        return this.bodyText;
    }
}
