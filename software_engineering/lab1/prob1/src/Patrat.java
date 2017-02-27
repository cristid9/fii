import java.util.ArrayList;

public class Patrat extends Figura {

    public Patrat(ArrayList<Point> pointsS) {
        super(pointsS);
        this.figureType = "square";
    }

    public Patrat() {}

    @Override
    public void draw() {
        System.out.println("a square?");

        for (Point p : this.points) {
            p.print();
        }
    }
}
