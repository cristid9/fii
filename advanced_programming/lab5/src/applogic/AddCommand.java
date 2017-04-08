package applogic;

import java.util.List;

public class AddCommand extends AbstractCommand implements Command {
    static final String MOVIE_TYPE = "movie";
    static final String SONG_TYPE = "song";

    public AddCommand() {
        super();
    }

    @Override
    public void doExecute(Catalog catalog) throws InvalidArgsException {

        switch (commandArgs.get(1)) {
            case MOVIE_TYPE:
                if (commandArgs.size() < 4) {
                    throw new InvalidArgsException();
                }
                catalog.add(new Movie(commandArgs.get(2), commandArgs.get(3)));
                System.out.println("movie added");
                break;
            case SONG_TYPE:
                if (commandArgs.size() < 4) {
                    throw new InvalidArgsException();
                }
                catalog.add(new Song(commandArgs.get(2), commandArgs.get(3)));
                System.out.println("Song added");
                break;
        }
    }

    @Override
    public void loadArgs(List<String> args) {
        this.commandArgs = args;
    }
}
