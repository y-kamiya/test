package http;

public enum Status {
    OK("200 OK")
    ;

    private final String text;

    private Status(String text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return this.text;
    }
}
