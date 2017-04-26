import de.congrace.exp4j.ExpressionBuilder;
import de.congrace.exp4j.UnknownFunctionException;
import de.congrace.exp4j.UnparsableExpressionException;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class ControlPanel extends JPanel {
    private JTextField numberOfShapes;
    private JTextField numberOfSides;
    private JTextField stroke;
    private JButton drawButton;
    private DrawingFrame df;

    private JTextField mathFunction;
    private JButton plotButton;
    private JButton interpolateButton;
    private JButton clearButton;

    public ControlPanel(DrawingFrame drawingFrame) {



        setLayout(new GridLayout(1,4));

        df = drawingFrame;

        numberOfShapes = new JTextField();
        numberOfSides = new JTextField();
        stroke = new JTextField();
        drawButton = new JButton("Draw");

        numberOfSides.setColumns(10);
        numberOfShapes.setColumns(10);
        stroke.setColumns(10);

        drawButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Random random = new Random();

                df.getCanvas().setStroke(Integer.parseInt(stroke.getText()));
                df.getCanvas().drawShapeAt(
                        random.nextInt(600),
                        random.nextInt(600),
                        Integer.parseInt(numberOfShapes.getText()),
                        Integer.parseInt(numberOfSides.getText()));
            }
        });

        add(numberOfShapes);
        add(numberOfSides);
        add(stroke);
        add(drawButton);

        mathFunction = new JTextField();
        plotButton = new JButton("Plot");

        plotButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ExpressionBuilder expressionBuilder = new ExpressionBuilder(mathFunction.getText());

                for (double x = -400; x < 400; x += 0.01) {
                    double result = 0;
                    try {
                        result = expressionBuilder.withVariable("x", x).build().calculate();
                        System.out.println(result);
                        df.getCanvas().setStroke(1);

                        df.getCanvas().drawShapeAt((int) (x + 400), (int) result + 200, 3, 10);
                    } catch (UnknownFunctionException e1) {
                        System.out.println("Something wen wrong");
                    } catch (UnparsableExpressionException e1) {
                        System.out.println("Unparsable function");
                    }
                }

            }
        });

        add(mathFunction);
        add(plotButton);

        interpolateButton = new JButton("interpolate");
        interpolateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                df.getCanvas().performInterpolation();
            }
        });

        add(interpolateButton);

        clearButton = new JButton("Clear");
        clearButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("Nu s-a putut efectua stergerea, ai facut ceva gresit");
            }
        });

        add(clearButton);

    }
}
