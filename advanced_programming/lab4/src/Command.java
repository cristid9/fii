import java.io.IOException;
import java.util.List;

public interface Command {
    void doExecute(Catalog catalog) throws InvalidArgsException, IOException;
    void loadArgs(List<String> args);
}
