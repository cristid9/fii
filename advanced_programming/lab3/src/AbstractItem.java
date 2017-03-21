public abstract class AbstractItem implements Item {
    protected String name;
    protected int weight;
    protected double value;

    public AbstractItem(String name, int weight, double value) {
        this.name = name;
        this.weight = weight;
        this.value = value;
    }
}
