import javax.swing.*;
import java.awt.*;

/**
 * Created by cristi on 25.04.2017.
 */
public class DrawingFrame extends JFrame {

    private ToolBar toolBar;
    private ControlPanel controlPanel;
    private Canvas canvas;

    public DrawingFrame() {
        setLayout(new FlowLayout());
        toolBar = new ToolBar();
        controlPanel = new ControlPanel(this);
        canvas = new Canvas();

        add(toolBar);
        add(controlPanel);
        add(canvas);
    }

    public static void main(String[] args) {
        DrawingFrame df = new DrawingFrame();
        df.pack();
        df.setVisible(true);
    }

    public Canvas getCanvas() {
        return canvas;
    }
}
