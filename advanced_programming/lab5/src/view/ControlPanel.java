package view;

import controller.AppController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ControlPanel extends JPanel implements ActionListener, View{

    private JButton save;
    private JButton exit;
    private JButton load;
    private JButton report;
    private JComboBox formats;

    private AppController appController;

    public ControlPanel(AppController appController) {

        this.appController = appController;
        this.setLayout(new GridLayout(1, 2));

        save = new JButton("save");
        exit = new JButton("exit");
        load = new JButton("load");
        report = new JButton("report");
        formats = new JComboBox(new String[] {"html", "pdf", "excel"});

        save.addActionListener(this);
        exit.addActionListener(this);
        load.addActionListener(this);
        report.addActionListener(this);

        add(save);
        add(exit);
        add(load);
        add(report);
        add(formats);
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if (actionEvent.getSource() == load) {
            appController.loadCatalog();
        } else if (actionEvent.getSource() == save) {
            appController.saveCatalog();
        } else if (actionEvent.getSource() == report) {
            appController.generateReport(formats.getSelectedItem().toString());
        } else if (actionEvent.getSource() == exit) {
            appController.exitApp();
        }

    }

    @Override
    public void setupUI() {

    }
}
