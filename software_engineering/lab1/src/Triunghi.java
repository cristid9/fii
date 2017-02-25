import java.util.ArrayList;

public class Triunghi extends Figura {

    public Triunghi(ArrayList<Point> points) {
        super(points);
        this.figureType = "triangle";
    }

    public Triunghi() {}

    @Override
    public void draw() {
        System.out.println("Asta e un tringhi");

        for (Point p : this.points) {
            p.print();
        }
    }


}
