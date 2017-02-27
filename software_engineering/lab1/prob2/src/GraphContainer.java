import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class GraphContainer {
    private Map<Integer, ArrayList<Point>> points;
    private Double min;

    /**
     * Inner class used to track the amount of padding spaces needed.
     */
    private class SpaceTracker {
        private final Integer rate = 30;
        private Integer spacesSoFar;
        private Double min;

        public SpaceTracker(Double min) {
            spacesSoFar = 0;
            this.min = min;
        }

        public Integer getSpaces(Point p) {
            Integer tmp;
            if (Double.compare(p.getX(), 0) < 0) {
                tmp = (int) ((Math.abs(min) * rate + p.getX() * rate ) - spacesSoFar);
                spacesSoFar += tmp;
                return tmp;
            }
            tmp = (int)(Math.abs(min) * rate + p.getX() * rate - spacesSoFar);
            spacesSoFar += tmp;
            return tmp;
        }
    }

    public GraphContainer(Double min) {
        this.min = min;
        this.points = new TreeMap<>(Collections.reverseOrder());
    }

    /**
     * Adds a point to the graph of this function.
     * @param p The point that will be added.
     */
    public void add(Point p) {
        Integer y = (int)(p.getY() * 10);
        if (points.get(y) == null) {
            ArrayList<Point> yContainer = new ArrayList<Point>();
            yContainer.add(p);
            points.put(y, yContainer);
        } else {
            points.get(y).add(p);
            points.get(y).sort((p1, p2) -> Double.compare(p1.getX(), p2.getX()));
        }
    }

    /**
     * Prints the text-representation of a graph to the stdout.
     */
    public void printRepresentation() {
        try {
            PrintWriter writer = new PrintWriter("/home/cristi/java/Lab2/src/out.txt", "UTF-8");

            for (Map.Entry<Integer, ArrayList<Point>> entry : points.entrySet()) {
                Integer x = entry.getKey();
                ArrayList<Point> yContainer = entry.getValue();
                SpaceTracker sp = new SpaceTracker(min);
                for (Point p : yContainer) {

                    int padding = sp.getSpaces(p);
                    for (int i = 0; i < padding; ++i) {
                        System.out.print(" ");
                        writer.print(" ");
                    }

                    System.out.print("*");
                    writer.print("*");
                }
                System.out.println("");
                writer.println("");
            }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
