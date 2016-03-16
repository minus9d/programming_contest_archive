import java.util.Scanner;
 
public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        Integer a = sc.nextInt();
        Integer b = sc.nextInt();
        System.out.println(a < b ? "Better" : "Worse");
        return;
    }
}
