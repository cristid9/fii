public class Runner {

    public static void main(String[] args) {
        Book b1 = new Book("Dragon Rising", 3, 5);
        Book b2 = new Book("A Blade in the Dark", 3, 5);
        Weapon w1 = new Weapon("Ancient Sword", 5, 10);

        Knapsack knapsack = new Knapsack(10);
        knapsack.add(b1);
        knapsack.add(b2);
        knapsack.add(w1);

        knapsack.solve();
    }
}
