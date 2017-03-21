import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Knapsack {
    private int capacity;
    private ArrayList<Item> items;
    private double[][] itemsMatrix;


    public Knapsack(int capacity) {
        this.capacity = capacity;
        items = new ArrayList<>();
        itemsMatrix = new double[capacity][capacity];
    }

    /**
     * prints wthe solution to the knapsack problem.
     */
    public void solve() {
        double currentTime = System.currentTimeMillis();

        List<Item> tmpItemContainer = new ArrayList<>();

        for (int j = 0; j < capacity; ++j) {
            itemsMatrix[0][j] = 0;
        }

        for (int i = 1; i < items.size(); ++i) {
            for (int j = 0; j < capacity; ++j) {
                if (items.get(i).getWeight() > j) {
                    itemsMatrix[i][j] = itemsMatrix[i - 1][j];
                } else {
                    itemsMatrix[i][j] = Math.max(itemsMatrix[i - 1][j], itemsMatrix[i - 1][j - items.get(i).getWeight()]
                            + items.get(i).getValue());

                    if ( j == capacity - 1) {
                        tmpItemContainer.add(items.get(i));
                    }
                }
            }
        }

        double endTime = System.currentTimeMillis();

        System.out.println("Timp: " + (endTime - currentTime) + " millis");

        System.out.println("Max value: " + itemsMatrix[items.size() - 1][capacity - 1]);
        printKnapsackElements();
        System.out.println("Solutions selected: ");
        for (Item item : tmpItemContainer) {
            System.out.println("\t" + item + " ");
        }
    }

    private void printKnapsackElements() {
        System.out.println("Available items: ");
        for (Item item : items) {
            System.out.println("\t" + item);
        }
    }

    public void add(Item item) {
        items.add(item);
    }
}
