import java.io.*;
import java.util.ArrayList;

public class FigureContainer {
    public ArrayList<Figura> figures;
    protected final String LOG_FILE = "/home/cristi/software_engineering/src/foo.bar";

    public FigureContainer(ArrayList<Figura> cstArg) {
        this.figures = cstArg;
    }

    public FigureContainer() {
        // empty constructor
        this.figures = new ArrayList<Figura>();
    }

    /**
     * @brief wrappe over `figures`.
     */
    public void addFigure(Figura figure) {
        System.err.println("Am mai bagat una");
        figures.add(figure);
    }

    public Figura getFigure(int index) {
        return figures.get(index);
    }

    /**
     * @brief Loads a serialized object from the default file.
     */
    public void loadContainer() {
        try {
            FileInputStream fileIn = new FileInputStream(this.LOG_FILE);
            ObjectInputStream in = new ObjectInputStream(fileIn);

            ArrayList<Figura> tmpFigures = (ArrayList<Figura>) in.readObject();
            this.figures = tmpFigures;

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
    public void serializeContainer() {
        try {

            FileOutputStream fileOut =
                    new FileOutputStream(this.LOG_FILE);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(this.figures);
            out.close();
            fileOut.close();

        } catch(IOException i) {
            i.printStackTrace();
        }
    }

    public void drawAll() {
        System.out.println("Uite am dat dump la container");
        for (Figura fg : this.figures) {
            fg.draw();
        }

    }

}
