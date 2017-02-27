import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        // Get function parameters from stdin
        Scanner in = new Scanner(System.in);

        Double a = in.nextDouble();
        Double b = in.nextDouble();
        Double c = in.nextDouble();

        // Get min, max, step from file
        File file = new File("/home/cristi/java/Lab2/src/input.txt");
        Scanner inputFile = null;
        try {
            inputFile = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        Double min = inputFile.nextDouble();
        Double max = inputFile.nextDouble();
        Double step = inputFile.nextDouble();

        // Display the graph
        PointGenerator pointGenerator = new PointGenerator(min, max, step, a, b, c);
        GraphContainer graphContainer = pointGenerator.getGraphContainer();
        graphContainer.printRepresentation();

    }
}
