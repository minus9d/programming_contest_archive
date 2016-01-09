import java.util.Scanner;
import java.util.Set;
import java.util.HashSet;
import java.math.BigInteger;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        int N = sc.nextInt();
        int K = sc.nextInt();
        long[] array = new long[N];

        for(int n = 0; n < N; ++n) {
            array[n] = sc.nextLong();
            if (array[n] == 0) {
                System.out.println(N);
                return;
            }
        }

        int i = 0;
        int j = 0;
        long mul = 1;
        int lenmax = 0;
        while(i < N && j < N) {
            mul *= array[j];
            // System.out.printf("i,j,mul=%d,%d,%d\n", i,j,mul);
            if (mul <= K) {
                lenmax = Math.max(lenmax, j - i + 1);
                ++j;
            }
            else {
                if (i == j) {
                    ++i;
                    ++j;
                    mul = 1;
                }
                else {
                    mul /= array[i];
                    mul /= array[j];
                    ++i;
                }
            }
        }

        System.out.println(lenmax);
    }
}

