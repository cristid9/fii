import controller.AppController;
import model.AppModel;

import javax.swing.*;
import java.awt.*;

public class MediaFrame extends JFrame {
    public static void main(String[] args) {
        MediaFrame mediaFrame = new MediaFrame();
        mediaFrame.setLayout(new GridLayout(3, 2));

        AppModel appModel = new AppModel();
        AppController appController = new AppController(appModel);

        mediaFrame.add(appController.getAppPanel());
        mediaFrame.add(appController.getCatalogList());
        mediaFrame.add(appController.getControlPanel());
        mediaFrame.pack();
        mediaFrame.setVisible(true);
    }
}
