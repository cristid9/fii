import com.sun.deploy.util.ArrayUtil;
import org.apache.batik.dom.GenericDOMImplementation;
import org.apache.batik.svggen.SVGGraphics2D;
import org.apache.batik.svggen.SVGGraphics2DIOException;
import org.apache.commons.lang.ArrayUtils;
import org.apache.commons.math3.analysis.UnivariateFunction;
import org.apache.commons.math3.analysis.interpolation.SplineInterpolator;
import org.apache.commons.math3.analysis.interpolation.UnivariateInterpolator;
import org.w3c.dom.DOMImplementation;
import org.w3c.dom.Document;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Random;

public class Canvas extends JPanel {

    private Graphics2D graphics;
    private BufferedImage image;
    private JLabel imageContainer;
    private Stroke currentStroke;
    private ArrayList<Double> xs = new ArrayList<>();
    private ArrayList<Double> ys = new ArrayList<>();

    public Canvas() {

        setBackground(Color.white);

        this.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                xs.add(new Double(e.getX()));
                ys.add(new Double(e.getY()));

                Random rand = new Random();
                drawShapeAt(e.getX(), e.getY(), 10, 10);

                repaint();
                System.out.println("dsf");
            }
        });

        BufferedImage image = new BufferedImage(800, 1200, BufferedImage.TYPE_INT_ARGB);
        graphics = image.createGraphics();
        currentStroke = graphics.getStroke();

        imageContainer = new JLabel(new ImageIcon(image));
        add(imageContainer);
    }

    public void setStroke(float stroke) {
        graphics.setStroke(new BasicStroke(stroke));
        currentStroke = graphics.getStroke();
    }

    public void drawShapeAt(int x, int y, int radius, int sides) {
        Random rand = new Random();
        graphics.setColor(new Color(0x020001));
        graphics.fill(new RegularPolygon(x, y, radius, sides));
        graphics.setStroke(currentStroke);
        repaint();
    }

    public void performInterpolation() {
        Double[] rawXs = new Double[xs.size()];
        Double[] rawYs = new Double[ys.size()];

        rawXs = xs.toArray(rawXs);
        rawYs = ys.toArray(rawYs);

        double[] okXs = ArrayUtils.toPrimitive(rawXs);
        double[] okYs = ArrayUtils.toPrimitive(rawYs);

        UnivariateInterpolator interpolator = new SplineInterpolator();
        UnivariateFunction function = interpolator.interpolate(okXs, okYs);


        DOMImplementation domImpl = GenericDOMImplementation.getDOMImplementation();

        String svgNS = "http://www.w3.org/2000/svg";
        Document document = domImpl.createDocument(svgNS, "svg", null);

        SVGGraphics2D svgGenerator = new SVGGraphics2D(document);

        for (double x = xs.get(0); x < xs.get(xs.size() - 1); x += 0.07) {
            drawShapeAt((int)x, (int) (function.value(x)), 3, 10);
            System.out.println(function.value(x));
            svgGenerator.fillRect((int)x, (int)(function.value(x)), 1, 1);
        }


        boolean useCSS = true;
        Writer out = null;
        try {
            out = new OutputStreamWriter(System.out, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        try {
            svgGenerator.stream(out, useCSS);
        } catch (SVGGraphics2DIOException e) {
            e.printStackTrace();
        }
    }
}
