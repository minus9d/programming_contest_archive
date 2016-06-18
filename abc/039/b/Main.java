import java.util.Scanner;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int X = sc.nextInt();
        for (int x = 1; x < 10000; ++x) {
            if (x*x*x*x == X) {
                System.out.println(x);
                return;
            }
        }
    }
}

