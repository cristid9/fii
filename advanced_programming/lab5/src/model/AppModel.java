package model;

import applogic.*;
import observers.ListObserver;
import observers.Observable;

import javax.xml.bind.JAXBException;
import java.io.IOException;
import java.util.Arrays;

public class AppModel implements Model, Observable {
    ListObserver listObserver;
    Catalog catalog = new Catalog();


    public void addCatalogItem(CatalogItem catalogItem) {
        catalog.add(catalogItem);
        try {
            catalog.marshal();
        } catch (JAXBException e) {
            e.printStackTrace();
        }
    }

    public void loadCatalog() {
        catalog.load(Catalog.serilizationPath);
        for (CatalogItem catalogItem : catalog.getItems()) {
            if (catalogItem instanceof Movie)
                notifyObserver(catalogItem.toString(), "movie");
            else
                notifyObserver(catalogItem.toString(), "song");
        }
    }

    public void playItem(String item) {
        System.out.println(item);
        for (CatalogItem catalogItem : catalog.getItems()) {
            if (catalogItem.toString().equals(item)) {
                try {
                    catalog.play(catalogItem.getItemPath());
                } catch (InvalidPathException e) {
                    e.printStackTrace();
                }
                return;
            }
        }
    }

    public void saveCatalog() {
        catalog.save();
    }

    // messy
    @Override
    public void registerObserver(ListObserver o) {
        listObserver = o;
    }

    @Override
    public void removeObserver(ListObserver o) {
        listObserver = null;
    }

    @Override
    public void notifyObserver(String value, String type) {
        listObserver.notifyEvent(value, type);
    }

    public void generateReport(String value) {
        ReportCommand reportCommand = new ReportCommand();
        reportCommand.loadArgs(Arrays.asList(new String[] {"report", value}));
        try {
            reportCommand.doExecute(catalog);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String getItemName(String stringRepresentation) {
        for (CatalogItem item : catalog.getItems()) {
            if (item.toString().equals(stringRepresentation)) {
                return item.getItemName();
            }
        }
        return null;
    }
}
