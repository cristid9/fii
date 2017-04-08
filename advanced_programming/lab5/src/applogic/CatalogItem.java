package applogic;

import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlSeeAlso;

@XmlRootElement
@XmlSeeAlso({Movie.class, Song.class})
public interface CatalogItem {
    void setItemName(String name);
    String getItemName();

    String getItemPath();
    void setItemPath(String name);

    String toString();
}
