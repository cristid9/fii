package view;

import controller.AppController;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AppPanel extends JPanel implements View, ActionListener {
    private AppController appController;
    private JButton addMenu;
    private JButton playButton;
    private JButton searchMenu;

    public AppPanel(AppController appController) {
        this.appController = appController;

        addMenu = new JButton("Launch add menu");
        playButton = new JButton("Play");
        searchMenu = new JButton("Launch search menu");

        addMenu.addActionListener(this);
        playButton.addActionListener(this);
        searchMenu.addActionListener(this);

        add(addMenu);
        add(playButton);
        add(searchMenu);
    }

    @Override
    public void setupUI() {

    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if (actionEvent.getSource() == addMenu) {
            appController.launchAddPopUp();
        } else if (actionEvent.getSource() == searchMenu) {
            appController.launchSearchDialog();
        } else if (actionEvent.getSource() == playButton) {
            appController.playItem(appController.getSelectedItem());
        }
    }
}
