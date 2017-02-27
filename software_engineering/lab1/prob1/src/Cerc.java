import java.util.ArrayList;

public class Cerc extends Figura {

    public Cerc(ArrayList<Point> pointsC) {
        super(pointsC);
        this.figureType = "circle";
    }

    public Cerc() {}

    public void draw() {
        System.out.println("Look, I am a circe");
        for (Point p : this.points) {
            p.print();
        }
    }
}
