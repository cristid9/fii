import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Catalog catalog = new Catalog();
//        catalog.add(new Movie("Anabelle", "/home/cristi/Downloads/Annabelle.2014.BRRip.XviD.AC3.RoSubbed-playXD/Sample.avi"));
//        catalog.add(new Song("Bungo Bungo", "/home/cristi/Desktop/a.MP3"));
//
//        try {
//            catalog.play("/home/cristi/Desktop/a.MP3");
//        } catch (InvalidPathException e) {
//            e.printStackTrace();
//        }
//
//        catalog.save();
//        catalog.load(Catalog.serilizationPath);
//
//        try {
//            catalog.play("/home/cristi/Downloads/Annabelle.2014.BRRip.XviD.AC3.RoSubbed-playXD/Sample.avi");
//        } catch (InvalidPathException e) {
//            e.printStackTrace();
//        }
//
//        catalog.list();

        CommandDispatcher cm = new CommandDispatcher(catalog);

        Scanner s = new Scanner(System.in);
        // read till EOF
        while (s.hasNextLine()) {
            String line = s.nextLine();
            String[] cArgs = line.split(" ");
            List<String> commandArgs = Arrays.asList(cArgs);
            try {
                cm.dispatch(commandArgs);
            } catch (InvalidArgsException e) {
                e.printStackTrace();
            }
        }

    }
}
