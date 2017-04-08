package observers;

public interface Observable {
    void registerObserver(ListObserver o);
    void removeObserver(ListObserver o);
    void notifyObserver(String value, String type);
}
