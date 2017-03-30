public class InvalidPathException extends Exception {
    public InvalidPathException(String message) {
        super(message);
    }

    public InvalidPathException() {
        super("Invalid Path");
    }
}
