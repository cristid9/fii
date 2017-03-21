import java.util.ArrayList;

public class LatinSquareGenerator {
    private LatinSquareTypes squareType;
    private int latinAlphabetLength = 26;
    private int greekAlphabetLength = 24;
    private ArrayList<ArrayList<String>> memoisedPermutations;
    private boolean[] takenMemoisationTableIndexes;
    private String latinStartingChar = "a";
    private String greekStartingChar = "\u03B1";
    private ArrayList<String> acumulator;
    private int limitCounter;
    private int generationLimit;


    public LatinSquareGenerator(LatinSquareTypes squareType) {
        this.squareType = squareType;
        memoisedPermutations = new ArrayList<>();

        int alphabetSize = squareType == LatinSquareTypes.LATIN ? latinAlphabetLength : greekAlphabetLength;
        takenMemoisationTableIndexes = new boolean[alphabetSize];

        resetMemoisationTable();

        acumulator = new ArrayList<>(Math.max(latinAlphabetLength, greekAlphabetLength));
        for (int i = 0; i < Math.max(latinAlphabetLength, greekAlphabetLength); ++i) {
            acumulator.add("");
        }
    }

    public int generate(int n, int limit) {
        limitCounter = 0;
        generationLimit = limit;
        if (squareType == LatinSquareTypes.LATIN) {
            generateMemoisationTable(latinStartingChar, 0, n, acumulator);
            int[] lineIndexes = new int[latinAlphabetLength];
            permuteMatrix(0, n, memoisedPermutations.size(), lineIndexes);
        } else {
            generateMemoisationTable(greekStartingChar, 0, n, acumulator);
            int[] lineIndexes = new int[greekAlphabetLength];
            permuteMatrix(0, n, memoisedPermutations.size(), lineIndexes);
        }

        return limitCounter;
    }

    public void generate(int n) {
        generate(n, -1);
    }

    /**
     * Pregenerates all n-restricted permutations for the desired alphabet.
     * @param startingChar The first character of the alphabet.
     * @param current The current element.
     * @param limit Size of a permutation.
     * @param acumulator Where the partial sollution is stored.
     */
    private void generateMemoisationTable(String startingChar, int current,
                                          int limit, ArrayList<String> acumulator) {
        if (current == limit) {
            ArrayList<String> tmp = new ArrayList<String>();

            for (String s : acumulator) {
                tmp.add(s);
            }

            memoisedPermutations.add(tmp);
            return;
        }

        for (int offset = 0; offset < limit; ++offset) {
            if (takenMemoisationTableIndexes[offset]) {
                continue;
            }

            takenMemoisationTableIndexes[offset] = true;
            acumulator.set(current, String.valueOf((char)(startingChar.toCharArray()[0] + offset)));
            generateMemoisationTable(startingChar, current + 1, limit, acumulator);
            takenMemoisationTableIndexes[offset] = false;
        }
    }

    private void resetMemoisationTable() {
        int alphabetSize = squareType == LatinSquareTypes.LATIN ? latinAlphabetLength : greekAlphabetLength;

        for (int i = 0; i < alphabetSize; ++i) {
            takenMemoisationTableIndexes[i] = false;
        }
    }

    private void permuteMatrix(int current, int n, int size, int[] lineIndices) {

        if (current == n) {

            if (!checkUniqueColum(lineIndices, n)) {
                return;
            }

            if (generationLimit != -1) {
                if (generationLimit == limitCounter) {
                    return;
                }
            }
            limitCounter++;

            for (int i = 0; i < n; ++i) {
                ArrayList<String> tmp = memoisedPermutations.get(lineIndices[i]);
                for (String lineElem : tmp) {
                    System.out.print(lineElem + " ");
                }
                System.out.println("");
            }
            System.out.println("");
            return;
        }

        for (int offset = current; offset < size; ++offset) {
            lineIndices[current] = offset;
            permuteMatrix(current + 1, n, size, lineIndices);
        }
    }

    private boolean checkUniqueColum(int[] lineIndexes, int n) {

        for (int col = 0; col < n; ++col) {
            for (int row = 0; row < n; ++row) {
                for (int rowCursor = row + 1; rowCursor < n; ++rowCursor) {
                    if (memoisedPermutations.get(lineIndexes[row]).get(col)
                            .equals(memoisedPermutations.get(lineIndexes[rowCursor]).get(col))) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
}
