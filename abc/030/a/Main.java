import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;

public class Main
{
    void run() {
        Scanner sc = new Scanner(System.in);
        int A = sc.nextInt();
        int B = sc.nextInt();
        int C = sc.nextInt();
        int D = sc.nextInt();
        int val = B * C - A * D;
        String s = "";
        if (val == 0) {
            s = "DRAW";
        } else if (val > 0) {
            s = "TAKAHASHI";
        } else {
            s = "AOKI";
        }

        System.out.println(s);
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
