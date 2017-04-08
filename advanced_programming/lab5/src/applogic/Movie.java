package applogic;

import java.io.Serializable;

public class Movie implements CatalogItem, Serializable {
    private String movieName;
    private String moviePath;

    public Movie() { }

    public Movie(String movieName, String moviePath) {
        this.movieName = movieName;
        this.moviePath = moviePath;
    }

    @Override
    public void setItemName(String name) {
        this.movieName = name;
    }

    @Override
    public String getItemName() {
        return movieName;
    }

    @Override
    public String getItemPath() {
        return moviePath;
    }

    @Override
    public void setItemPath(String path) {
        moviePath = path;
    }

    @Override
    public String toString() {
        return "Movie(" +  movieName + ")";
    }
}
