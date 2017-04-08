package applogic;

import java.util.List;

public class LoadCommand extends AbstractCommand implements Command {
    public LoadCommand() {
        super();
    }

    @Override
    public void doExecute(Catalog catalog) {
        catalog.load(Catalog.serilizationPath);
        System.out.println("Catalog loaded successfully");
    }

    @Override
    public void loadArgs(List<String> args) {
        this.commandArgs = args;
    }
}
