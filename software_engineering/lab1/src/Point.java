import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class Point implements Serializable {
    public Integer x;
    public Integer y;

    public Point (Integer x, Integer y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public String toString() {
        return x + " " + y;
    }

    public void print() {
        System.out.println("(" + x + ", " + y + ")");
    }
}
