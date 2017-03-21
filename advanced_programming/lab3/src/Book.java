public class Book extends AbstractItem implements Item {

    public Book(String name, int weight, double value) {
        super(name, weight, value);
    }

    public String getName() {
        return name;
    }

    public int getWeight() {
        return weight;
    }

    public double getValue() {
        return value;
    }

    void setName(String name) {
        this.name = name;
    }

    void setWeight(int weight) {
        this.weight = weight;
    }

    void setValue(double value) {
        this.value = value;
    }

    public boolean equals(Weapon o) {
        if (name.equals(o.getName())
                && value == o.getValue()
                && weight == o.getWeight()) {
            return true;
        }
        return false;
    }

    @Override
    public String toString() {
        return "[Book] name=" + name + ": weight=" + weight + "  value" + value;
    }
}
