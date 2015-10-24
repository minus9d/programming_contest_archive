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

        if (N >= 12) N -= 12;

        double ang1 = (double)360 * N / 12 + (double)30 * M / 60;
        double ang2 = (double)360 * M / 60;
        
        double diff = max(ang2, ang1) - min(ang2, ang1);
        if (diff > 180.0) diff = 360.0 - diff;
        System.out.printf("%.09f", diff);

    }

    public static void main(String[] args) {
        new Main().run();
    }
}
