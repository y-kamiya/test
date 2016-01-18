package http;

public enum ContentType {
    TEXT_HTML("text/html")
    ;

    private final String text;

    private ContentType(String text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return this.text;
    }
}

