package view;

import controller.AppController;
import observers.ListObserver;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CatalogList extends JPanel implements View, ActionListener, ListObserver {
    DefaultListModel<String> model = new DefaultListModel<>();

    private AppController appController;
    private JList list;
    private JButton playButton;
    private DefaultMutableTreeNode movies = new DefaultMutableTreeNode("Movies");
    private DefaultMutableTreeNode songs = new DefaultMutableTreeNode("Songs");
    private JTree catalogTree;
    private JScrollPane scrollTreeView;

    public CatalogList(AppController appController) {

        this.appController = appController;
        this.setBorder(BorderFactory.createTitledBorder("Catalog Items"));

        list = new JList<String>(model);
        playButton = new JButton("Play ");
        DefaultMutableTreeNode catalogNode = new DefaultMutableTreeNode("Catalog                                  ");
        catalogNode.add(movies);
        catalogNode.add(songs);
        catalogTree = new JTree(catalogNode);
        catalogTree.setEditable(true);

        scrollTreeView = new JScrollPane(catalogTree);

        add(scrollTreeView);
        add(playButton);

        playButton.addActionListener(this);
    }

    public void addItem(String item, String type) {

        if (type.equals("song"))
            songs.add(new DefaultMutableTreeNode(item));
        else
            movies.add(new DefaultMutableTreeNode(item));

        ((DefaultTreeModel) catalogTree.getModel()).reload();
        for (int i = 0; i < catalogTree.getRowCount(); ++i) {
            catalogTree.expandRow(i);
        }
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if (actionEvent.getSource() == playButton) {
            appController.playItem(catalogTree.getSelectionPath().getLastPathComponent().toString());
        }
    }

    @Override
    public void setupUI() {

    }

    @Override
    public void notifyEvent(String value, String type) {
        addItem(value, type);
    }

    public String getSelectedItem() {
        return catalogTree.getSelectionPath().getLastPathComponent().toString();
    }
}
