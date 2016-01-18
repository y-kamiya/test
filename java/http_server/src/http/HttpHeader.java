package http;

import static http.Constant.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class HttpHeader {
    
    private final String headerText;
    private String method;
    private String path;
    private Map<String, String> messageHeaders = new HashMap<>();

    public HttpHeader(BufferedReader br) throws IOException {
        StringBuilder header = new StringBuilder();

        header.append(this.readRequestLine(br))
              .append(this.readMessageLine(br));

        this.headerText = header.toString();
    }

    private String readRequestLine(BufferedReader br) throws IOException {
        String requestLine = br.readLine();

        String[] parts = requestLine.split(" ");
        this.method = parts[0].toUpperCase();
        this.path = parts[1];
        return requestLine + CRLF;
    }

    private StringBuilder readMessageLine(BufferedReader br) throws IOException {
        StringBuilder sb = new StringBuilder();

        String messageLine = br.readLine();

        while (messageLine != null && !messageLine.isEmpty()) {
            this.putMessageLine(messageLine);
            sb.append(messageLine + CRLF);
            messageLine = br.readLine();
        }
        return sb;
    }

    private void putMessageLine(String messageLine) {
        String[] parts = messageLine.split(":");
        this.messageHeaders.put(parts[0].trim(), parts[1].trim());
    }

    public String getHeaderText() {
        return this.headerText;
    }

    public int getContentLength() {
        String contentLength = this.messageHeaders.getOrDefault("Content-Length", "0");
        return Integer.parseInt(contentLength);
    }

    public boolean isGetMethod() {
        return this.method.equals("GET");
    }

    public String getPath() {
        return this.path;
    }
}

