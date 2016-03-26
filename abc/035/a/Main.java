import java.util.Scanner;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int w = sc.nextInt();
        int h = sc.nextInt();
        if ((h % 3 == 0) && (w == h / 3 * 4)) {
            System.out.println("4:3");
        }
        else {
            System.out.println("16:9");
        }
    }
}
