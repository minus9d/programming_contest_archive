import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;

public class Main
{
    void run() {
        Scanner sc = new Scanner(System.in);
        int H = sc.nextInt();
        int W = sc.nextInt();

        String[] cells = new String[H];

        for (int h = 0; h < H; ++h)
        {
            cells[h] = sc.next();
        }

        for (int h = 0; h < H; ++h)
        {
            for (int w = 0; w < W; ++w)
            {
                if (cells[h].charAt(w) == '#') {
                    System.out.printf("#");
                }
                else {
                    int[] dh = new int[]{0, 1, -1};
                    int[] dw = new int[]{0, 1, -1};
                    int cnt = 0;
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            int h2 = h + dh[i];
                            int w2 = w + dw[j];
                            if ((i != 0 || j != 0)
                                && 0 <= h2 && h2 < H
                                && 0 <= w2 && w2 < W
                                && cells[h2].charAt(w2) == '#') {
                                ++cnt;
                            }
                        }
                    }
                    System.out.printf("%d", cnt);
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
