import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;

public class Main
{
    void run() {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int M = sc.nextInt();
        int X = sc.nextInt();
        int Y = sc.nextInt();
        int[] As = new int[N];
        int[] Bs = new int[M];
        for(int i = 0; i < N; ++i) {
            As[i] = sc.nextInt();
        }
        for(int i = 0; i < M; ++i) {
            Bs[i] = sc.nextInt();
        }

        boolean atA = true;
        int time = 0;
        int idxA = 0;
        int idxB = 0;
        int ret = 0;
        while(true) {
            // System.out.println("Time: " + time);
            
            if (atA) {
                if (idxA >= N) break;
                if (As[idxA] >= time) {
                    time = As[idxA] + X;
                    atA = false;
                }
                ++idxA;
            }
            else {
                if (idxB >= M) break;
                if (Bs[idxB] >= time) {
                    time = Bs[idxB] + Y;
                    atA = true;
                    ++ret;
                }
                ++idxB;
            }
        }

        System.out.println(ret);
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
