import java.io.*;
import java.util.ArrayDeque;
import java.util.ArrayList;

public class Figura implements Serializable {

    protected final String LOG_FILE = "/home/cristi/software_engineering/src/foo.bar";
    protected String figureType;
    protected ArrayList<Point> points;

    public Figura(ArrayList<Point> points) {
        this.points = points;
    }

    public Figura() {}

    public void setPoints(ArrayList<Point> points) {
        this.points = points;
    }

    public void draw() {
        // override in child
        System.out.println("I am drawing");
    }

    /**
     * @brief Loads a serialized object from the default file.
     */
    public void loadObject() {
        try {
            FileInputStream fileIn = new FileInputStream(this.LOG_FILE);
            ObjectInputStream in = new ObjectInputStream(fileIn);

            ArrayList<Point> tmpPoints = (ArrayList<Point>) in.readObject();
            this.points = tmpPoints;

            in.close();
            fileIn.close();
        } catch(IOException i) {
            i.printStackTrace();
            return;
        } catch(ClassNotFoundException c) {
            c.printStackTrace();
            return;
        }
    }

    /**
     * @brief Stores the configuration of the current object in the default
     *       file.
     */
    public void serializeFigure() {
        try {

            FileOutputStream fileOut =
                    new FileOutputStream(this.LOG_FILE);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(this.points);
            out.close();
            fileOut.close();

        } catch(IOException i) {
            i.printStackTrace();
        }
    }



}
