import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.util.*;

public class Main {
    static List<String> sourceFileLines = new ArrayList<>();
    static List<String> linesWithKey = new ArrayList<>();

    public static void main(String[] args) {
        prepareFiles();

        // Experiment 1
        LinkedList<String> transactions = getTransactions();
        int lookupCountSum = 0;
        for (String transaction : transactions) {
            int lookUpCounts = 0;
            try {
                File sourceFile = new File("randomizedFile.txt");
                Scanner myReader = new Scanner(sourceFile);
                while (myReader.hasNextLine()) {
                    String data = myReader.nextLine();
                    lookUpCounts++;
                    if (data.length() >= 4) {
                        if (transaction.equals(data.substring(0, 4))) {
                            break;
                        }
                    }
                }
                lookupCountSum += lookUpCounts;
                myReader.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                return;
            }
        }
        System.out.println("---Linear search on randomized file");
        System.out.println("Average lookup counts: " + (double) lookupCountSum / transactions.size());
        System.out.println("Overall lines in the file: " + sourceFileLines.size());

        //Experiment 2
        transactions = getTransactions();
        lookupCountSum = 0;
        for (String transaction : transactions) {
            int lookUpCounts = 0;
            try {
                File sourceFile = new File("fileWithKey.txt");
                Scanner myReader = new Scanner(sourceFile);
                while (myReader.hasNextLine()) {
                    String data = myReader.nextLine();
                    lookUpCounts++;
                    if (data.length() >= 4) {
                        if (transaction.equals(data.substring(0, 4))) {
                            break;
                        }
                    }
                }
                lookupCountSum += lookUpCounts;
                myReader.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                return;
            }
        }
        System.out.println("---Linear search on ordered file");
        System.out.println("Average lookup counts: " + (double) lookupCountSum / transactions.size());
        System.out.println("Overall lines in the file: " + sourceFileLines.size());
    }

    private static LinkedList<String> getTransactions() {
        LinkedList<String> transactions = new LinkedList<>();
        Random random = new Random();
        for (int i = 0; i < 20; i++) {
            transactions.add(get4DigitString(random.nextInt(sourceFileLines.size())));
        }
        return transactions;
    }

    private static void prepareFiles() {
        // Reade the source file
        try {
            File sourceFile = new File("someFile.txt");
            Scanner myReader = new Scanner(sourceFile);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                sourceFileLines.add(data);
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        }

        // Create the file with keys
        try {
            FileWriter myWriter = new FileWriter("fileWithKey.txt");

            for (int i = 0; i < sourceFileLines.size(); i++) {
                String keyDigits = get4DigitString(i);
                myWriter.write(keyDigits + sourceFileLines.get(i) + "\n");
                linesWithKey.add(keyDigits + sourceFileLines.get(i));
            }
            myWriter.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Create the randomized file
        try {
            Random random = new Random();
            FileWriter writer = new FileWriter("randomizedFile.txt");
            for (int i = 0; i < sourceFileLines.size(); i++) {
                int randomListIndex = random.nextInt(linesWithKey.size());
                writer.write(linesWithKey.get(randomListIndex) + "\n");
                linesWithKey.remove(randomListIndex);
            }
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String get4DigitString(int intNumber) {
        String result = "";
        int count = 1;
        for (; count <= 4; count++) {
            if (intNumber / (Math.pow(10, count)) < 1) {
                break;
            }
        }
        for (int i = 0; i < 4 - count; i++) {
            result += "0";
        }
        return result + intNumber;
    }

}
