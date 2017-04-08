package applogic;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by cristi on 28.03.17.
 */
public class CommandDispatcher {
    Map<String, Command> commands;
    private Catalog catalog;

    public CommandDispatcher(Catalog catalog) {
        this.catalog = catalog;

        commands = new HashMap<>();

        commands.put("add", new AddCommand());
        commands.put("list", new ListCommand());
        commands.put("save", new SaveCommand());
        commands.put("load", new LoadCommand());
        commands.put("play", new PlayCommand());
        commands.put("report", new ReportCommand());
        commands.put("", new EmptyCommand());
    }

    public void dispatch(List<String> args) throws InvalidArgsException{
        if (args.size() == 0) {
            throw new InvalidArgsException();
        }

        commands.get(args.get(0)).loadArgs(args);
        try {
            commands.get(args.get(0)).doExecute(catalog);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void setCatalog(Catalog catalog) {
        this.catalog = catalog;
    }

    public Catalog getCatalog() {
        return catalog;
    }
}
