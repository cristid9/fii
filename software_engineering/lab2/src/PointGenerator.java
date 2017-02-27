
public class PointGenerator {
    private Double min;
    private Double max;
    private Double step;
    private Double a;
    private Double b;
    private Double c;

    public PointGenerator(Double min, Double max, Double step, Double a, Double b, Double c) {
        this.min  = min;
        this.max  = max;
        this.step = step;
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public GraphContainer getGraphContainer() {
        GraphContainer gc = new GraphContainer(min);
        Double xValue = min;
        while (xValue <= max) {
            Double yValue = a * Math.pow(xValue, 2) + b * xValue + c;
            Point p = new Point(xValue, yValue);
            gc.add(p);
            xValue += step;
        }

        return gc;
    }
}
