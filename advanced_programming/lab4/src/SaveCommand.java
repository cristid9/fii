import java.util.List;

public class SaveCommand extends AbstractCommand implements Command {
    public SaveCommand() {
        super();
    }

    @Override
    public void doExecute(Catalog catalog) {
        catalog.save();
        System.out.println("Catalog saved successfully");
    }

    @Override
    public void loadArgs(List<String> args) {
        this.commandArgs = args;
    }
}
