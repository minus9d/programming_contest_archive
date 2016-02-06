import java.util.Scanner;
 
public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        String a = sc.next();
        char ch = a.charAt(0);
        for(int i = 1; i < 4; ++i) {
            if (ch != a.charAt(i)) {
                System.out.println("DIFFERENT");
                return;
            }
        }
        System.out.println("SAME");
        return;
    }
}
