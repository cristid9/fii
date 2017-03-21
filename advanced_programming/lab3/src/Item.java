public interface Item {

    String getName();
    int getWeight();
    double getValue();

    default int getProfitFactor() {
        System.out.println("Printing the default profit factor");
        return 0;
    }
}
