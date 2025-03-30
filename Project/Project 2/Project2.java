import java.util.Scanner;

public class VectorCalculation {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the dimension of the vectors");
        int n = scanner.nextInt();
        int[] a = new int[n];
        int[] b = new int[n];
        long result = 0;
        for (int i = 0 ; i < n ; i++){
            a[i] = scanner.nextInt();
        }
        for (int i = 0 ; i < n ; i++){
            b[i] = scanner.nextInt();
        }

        //Start of the timer
        //Input time doesn't count in due to the potential of huge timing errors
        long startTime = System.nanoTime();

        for (int i = 0 ; i < n ; i++){
            result += a[i] * b[i];
        }
        System.out.println();
        System.out.println(result);

        //End of the timer
        for (int i = 0; i < 1000000; i++);
        long endTime = System.nanoTime();
        long durationNano = endTime - startTime;
        double durationSeconds = durationNano / 1e9;
        System.out.printf("Time elapsed: %.9f seconds\n", durationSeconds);

    }
}
