import java.util.ArrayList;

public class Runner {

    public static void main(String[] args) {
        FigureContainer fc = new FigureContainer();

        // Cerc
        ArrayList<Point> circlePoints = new ArrayList<Point>();
        circlePoints.add(new Point(1, 2));
        circlePoints.add(new Point(3, 4));

        Cerc crc = new Cerc(circlePoints);
        crc.draw();
        crc.serializeFigure();
        System.out.println("Serializin', next deserialize an object");

        Cerc crc1 = new Cerc();
        crc1.loadObject();
        crc1.draw();

        // Patrat
        ArrayList<Point> squarePoints = new ArrayList<Point>();
        squarePoints.add(new Point(1, 2));
        squarePoints.add(new Point(3, 4));
        squarePoints.add(new Point(9, 6));
        squarePoints.add(new Point(5, 6));

        Patrat p = new Patrat(squarePoints);
        p.draw();
        p.serializeFigure();
        System.out.println("Serializin', next deserialize an object");


        Patrat p2 = new Patrat();
        p2.loadObject();
        p2.draw();

        // Triunghi
        ArrayList<Point> trianglePoints = new ArrayList<Point>();
        trianglePoints.add(new Point(1, 2));
        trianglePoints.add(new Point(3, 4));
        trianglePoints.add(new Point(9, 6));

        Triunghi trg = new Triunghi(trianglePoints);
        trg.draw();
        trg.serializeFigure();
        System.out.println("Serializin', next deserialize an object");

        Triunghi trg2 = new Triunghi();
        trg2.loadObject();
        trg2.draw();

        FigureContainer figCont = new FigureContainer();
        figCont.addFigure(trg);
        figCont.addFigure(crc);
        figCont.addFigure(p);

        figCont.drawAll();

        figCont.serializeContainer();

        FigureContainer f2 = new FigureContainer();
        f2.loadContainer();
        f2.drawAll();
    }
}
