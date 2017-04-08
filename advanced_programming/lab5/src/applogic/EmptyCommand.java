package applogic;

import java.util.List;

/**
 * Created by cristi on 28.03.17.
 */
public class EmptyCommand extends AbstractCommand implements Command {
    @Override
    public void doExecute(Catalog catalog) throws InvalidArgsException {
        System.out.println("Insert a command..");
    }

    @Override
    public void loadArgs(List<String> args) {
        this.commandArgs = args;
    }
}
