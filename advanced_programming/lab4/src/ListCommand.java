import java.util.List;

public class ListCommand extends AbstractCommand implements Command {
    public ListCommand() {
        super();
    }

    @Override
    public void doExecute(Catalog catalog) {
        catalog.list();
        System.out.println("Catalog listed successfully");
    }

    @Override
    public void loadArgs(List<String> args) {
        this.commandArgs = args;
    }
}
