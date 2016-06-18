import java.util.Scanner;
import static java.util.Arrays.*;
import java.util.*;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int N = sc.nextInt();

        ArrayList<Integer> streaks = new ArrayList<Integer>();
        int prev = -1;
        int cont = 0;
        for(int i = 0; i < N; ++i) {
            int tmp = sc.nextInt();
            if (tmp > prev) {
                cont++;
            }
            else {
                streaks.add(cont);
                cont = 1;
            }
            prev = tmp;
        }
        streaks.add(cont);

        long ans = 0;
        for (int i = 0; i < streaks.size(); ++i) {
            // overflow注意
            Long n = Long.valueOf(streaks.get(i));
            ans += n * (n + 1) / 2;
        }

		System.out.println(ans);
    }
}

