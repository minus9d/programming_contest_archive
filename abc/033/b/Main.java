import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int N = sc.nextInt();
        
        String[] Ss = new String[N];
        int[] Ps = new int[N];

        int sum = 0;
        for(int i = 0; i < N; ++i) {
            Ss[i] = sc.next();
            Ps[i] = sc.nextInt();
            sum += Ps[i];
        }
        
        for(int i = 0; i < N; ++i) {
            if (Ps[i] > (sum - Ps[i])) {
                System.out.println(Ss[i]);
                return;
            }
        }
        System.out.println("atcoder");
        return;
    }
}

