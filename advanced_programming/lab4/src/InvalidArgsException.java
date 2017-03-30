public class InvalidArgsException extends Exception {
    public InvalidArgsException() {
        super("Invalid arguments passed to the command");
    }
}
