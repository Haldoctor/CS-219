import java.util.Scanner;
import java.util.Random;
import java.io.*;

public class generateVector {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();

        int n = scanner.nextInt();
        int[] a = new int[n];
        int[] b = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = random.nextInt();
            b[i] = random.nextInt();
        }

        try (PrintWriter pw = new PrintWriter(new FileWriter("output.txt"))) {
            // 新增维度输出
            pw.println(n);          // 写入文件
            System.out.println(n);  // 控制台输出

            // 输出数组a到控制台和文件
            for (int i = 0; i < n; i++) {
                String output = String.format("%d ", a[i]);
                System.out.print(output);
                pw.print(output);
            }
            System.out.println();
            pw.println();

            // 输出数组b到控制台和文件
            for (int i = 0; i < n; i++) {
                String output = String.format("%d ", b[i]);
                System.out.print(output);
                pw.print(output);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
