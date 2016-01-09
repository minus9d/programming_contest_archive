import java.util.Scanner;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int a = sc.nextInt();
        int b = sc.nextInt();
        int n = sc.nextInt();
	while (true) {
	    if (n % a == 0 && n % b == 0) {
		System.out.println(n);
		return;
	    }
	    ++n;
	}
    }
}

