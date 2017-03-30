import java.io.Serializable;

public class Song implements CatalogItem, Serializable {
    private String songName;
    private String songPath;

    public Song(String songName, String songPath) {
        this.songName = songName;
        this.songPath = songPath;
    }

    public Song() { }

    @Override
    public void setItemName(String name) {
        songName = name;
    }

    @Override
    public String getItemName() {
        return songName;
    }

    @Override
    public String getItemPath() {
        return songPath;
    }

    @Override
    public void setItemPath(String path) {
        songPath = path;
    }

    @Override
    public String toString() {
        return "Song (" + songName + ")";
    }
}
