import java.util.Scanner;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int N = sc.nextInt();
        double correct = N * 99 / 100;
        double wrong = (10000 - N) / 100;
        System.out.println(wrong / (wrong + correct) * 100);
    }
}

