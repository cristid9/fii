package applogic;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.bind.annotation.XmlList;
import javax.xml.bind.annotation.XmlRootElement;
import java.awt.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

@XmlRootElement
public class Catalog implements Serializable {
    public List<CatalogItem> getItems() {
        return items;
    }


    private List<CatalogItem> items;
    @XmlList
    private List<String> hackishSerializationList = new ArrayList<>();

    public static String serilizationPath = "/home/cristi/Desktop/serialization/foo.bar";

    public Catalog() {
        items = new ArrayList<>();
    }

    public Catalog(List<CatalogItem> items) {
        this.items = items;
    }

    public void add(CatalogItem item) {
        items.add(item);
    }

    public void list() {
        for (CatalogItem item : items) {
            System.out.println(item);
        }
    }

    public Catalog unmarshal() throws JAXBException {
        JAXBContext jc = JAXBContext.newInstance(Catalog.class);

        Unmarshaller unmarshaller = jc.createUnmarshaller();
        File xml = new File("output.xml");
        Catalog catalog = (Catalog) unmarshaller.unmarshal(xml);

        Marshaller marshaller = jc.createMarshaller();
        marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
        marshaller.marshal(catalog, System.out);

        return catalog;
    }

    public void marshal() throws JAXBException {

        for (CatalogItem item : getItems()) {
            hackishSerializationList.add(item.toString());
        }

        File file = new File("output.xml");
        JAXBContext jaxbContext = JAXBContext.newInstance(Catalog.class, Movie.class, Song.class);
        Marshaller jaxbMarshaller = jaxbContext.createMarshaller();
        jaxbMarshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);

        jaxbMarshaller.marshal(this, file);
        jaxbMarshaller.marshal(this, System.out);
    }

    private boolean isValidPath(String path) {
        for (CatalogItem item : items) {
            if (item.getItemPath().equals(path)) {
                return true;
            }
        }

        return false;
    }

    public List<String> generateDataSource() {
        List<String> ds = new ArrayList<>();

        for (CatalogItem item : items) {
//            Map<String, String> it = new HashMap<>();
//            it.put("Item", item.getItemPath());
            ds.add(item.getItemName());
        }

        return ds;
    }

    public void play(String path) throws InvalidPathException {
        if (!isValidPath(path)) {
            throw new InvalidPathException();
        }

        File file = new File(path);
        Desktop desktop = Desktop.getDesktop();

        try {
            desktop.open(file);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void save() {
        try {
            FileOutputStream fileOut = new FileOutputStream(Catalog.serilizationPath);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(this.items);
            out.close();
            fileOut.close();

        } catch(IOException i) {
            i.printStackTrace();
        }
    }

    public void load(String path) {
        try {
            FileInputStream fileIn = new FileInputStream(path);
            ObjectInputStream in = new ObjectInputStream(fileIn);

            ArrayList<CatalogItem> items = (ArrayList<CatalogItem>) in.readObject();
            this.items = items;

            in.close();
            fileIn.close();
        } catch(IOException i) {
            i.printStackTrace();
            return;
        } catch(ClassNotFoundException c) {
            c.printStackTrace();
            return;
        }

    }
}
