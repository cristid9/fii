package view;

import applogic.CatalogItem;
import applogic.Movie;
import applogic.Song;
import controller.AppController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ItemForm extends JFrame implements View, ActionListener {

    private AppController appController;
    private JTextField name;
    private JTextField path;
    private JButton addButton;
    private JComboBox itemsList;


    public ItemForm(AppController appController) {
        this.appController = appController;
        this.setLayout(new GridLayout(4, 1));
        SpinnerModel model = new SpinnerNumberModel(1950, 1900, 2017, 1);

        name = new JTextField("Name");
        path = new JTextField("Path");
        addButton = new JButton("Add");
        itemsList = new JComboBox(new String[] {"movie", "song"});

        addButton.addActionListener(this);

        add(name);
        add(path);
        add(addButton);
        add(itemsList);
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if (actionEvent.getSource() == addButton) {
            CatalogItem item;
            if (this.itemsList.getSelectedItem().equals("movie")) {
                item = new Movie();
            } else {
                item = new Song();
            }

            item.setItemName(name.getText());
            item.setItemPath(path.getText());

            appController.addCatalogItem(item, this.itemsList.getSelectedItem().toString());
        }
    }

    @Override
    public void setupUI() {

    }
}
