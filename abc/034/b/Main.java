import java.util.Scanner;
 
public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        Integer a = sc.nextInt();
        System.out.println((a % 2 == 1) ? (a + 1) : (a - 1));
        return;
    }
}
