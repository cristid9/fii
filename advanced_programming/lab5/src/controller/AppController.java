package controller;

import applogic.CatalogItem;
import model.AppModel;
import view.*;

public class AppController implements Controller {
    ItemForm itemForm;
    CatalogList catalogList;
    ControlPanel controlPanel;
    AppPanel appPanel;
    AppModel appModel;
    SearchDialog searchDialog;


    public AppController(AppModel appModel) {
        itemForm = new ItemForm(this);
        catalogList = new CatalogList(this);
        controlPanel = new ControlPanel(this);
        appPanel = new AppPanel(this);
        searchDialog = new SearchDialog(this);

        this.appModel = appModel;
        this.appModel.registerObserver(catalogList);
    }

    public void addCatalogItem(CatalogItem item, String type) {
        appModel.addCatalogItem(item);
        catalogList.addItem(item.toString(), type);
    }

    public ItemForm getItemForm() {
        return itemForm;
    }

    public CatalogList getCatalogList() {
        return catalogList;
    }

    public ControlPanel getControlPanel() {
        return controlPanel;
    }

    public void loadCatalog() {
        appModel.loadCatalog();
    }

    public void playItem(String item) {
        appModel.playItem(item);
    }

    public void saveCatalog() {
        appModel.saveCatalog();
    }

    public void generateReport(String value) {
        appModel.generateReport(value);
    }

    public void exitApp() {
        System.exit(0);
    }

    public AppPanel getAppPanel() {
        return appPanel;
    }

    public void launchAddPopUp() {
        itemForm.pack();
        itemForm.setVisible(true);
    }

    public String getSelectedItem() {
        return catalogList.getSelectedItem();
    }

    public void launchSearchDialog() {
        System.out.println(getItemName(catalogList.getSelectedItem()));
        searchDialog.setSearchString(getItemName(catalogList.getSelectedItem()));
        searchDialog.pack();
        searchDialog.setVisible(true);
    }

    public String getItemName(String stringRepresentation) {
        return appModel.getItemName(stringRepresentation);
    }
}
