public class Main {

    public static void main(String[] args) throws Exception {

        if (args.length == 0) {
            LatinSquareGenerator ls = new LatinSquareGenerator(LatinSquareTypes.LATIN);
            ls.generate(3, 1);
        } else if (args.length == 2) {
            if (args[1].equals("latin")) {
                LatinSquareGenerator ls = new LatinSquareGenerator(LatinSquareTypes.LATIN);
                ls.generate(Integer.valueOf(args[0]), 1);
            } else if (args[1].equals("greek")) {
                LatinSquareGenerator ls = new LatinSquareGenerator(LatinSquareTypes.GREEK);
                ls.generate(Integer.valueOf(args[0]), 1);
            } else {
                throw new Exception("Undefined alphabet");
            }
        } else if (args.length == 3) {

            long startTime;
            long endTime;

            int count;
            if (args[1].equals("latin")) {
                LatinSquareGenerator ls = new LatinSquareGenerator(LatinSquareTypes.LATIN);
                startTime = System.currentTimeMillis();
                count = ls.generate(Integer.valueOf(args[0]), Integer.valueOf(args[2]));
                endTime = System.currentTimeMillis();
            } else if (args[1].equals("greek")) {
                LatinSquareGenerator ls = new LatinSquareGenerator(LatinSquareTypes.GREEK);
                startTime = System.currentTimeMillis();
                count = ls.generate(Integer.valueOf(args[0]), Integer.valueOf(args[2]));
                endTime = System.currentTimeMillis();
            } else {
                throw new Exception("Undefined alphabet");
            }

            System.out.println(count + " many squares have been generated");
            System.out.println("The running time of this operation is " + (endTime - startTime) + "milliseconds");
        }
    }
}
