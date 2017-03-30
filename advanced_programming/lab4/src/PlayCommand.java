import java.util.List;

public class PlayCommand extends AbstractCommand implements Command {
    public PlayCommand() {
        super();
    }

    @Override
    public void doExecute(Catalog catalog) throws InvalidArgsException {
        if (commandArgs.size() < 2) {
            throw new InvalidArgsException();
        }

        try {
            catalog.play(commandArgs.get(1));
        } catch (InvalidPathException e) {
            e.printStackTrace();
        }
        System.out.println("item played successfully");
    }

    @Override
    public void loadArgs(List<String> args) {
        this.commandArgs = args;
    }
}
