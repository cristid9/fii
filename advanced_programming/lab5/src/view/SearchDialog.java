package view;

import controller.AppController;
import misc.GoogleSearcher;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.List;

public class SearchDialog extends JFrame implements View, ActionListener {
    private AppController appController;
    private JList results;
    private DefaultListModel listModel;
    private JScrollPane scrollPane;

    public SearchDialog(AppController appController) {
        this.appController = appController;
        listModel = new DefaultListModel();
        results = new JList(listModel);
        scrollPane = new JScrollPane(results);

        add(scrollPane);
    }

    public void setSearchString(String item) {
        List<String> results = null;
        try {
            results = GoogleSearcher.search(item);
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println(results);

        for (String result : results) {
            listModel.addElement(result);
        }
    }


    @Override
    public void actionPerformed(ActionEvent actionEvent) {

    }

    @Override
    public void setupUI() {

    }
}
