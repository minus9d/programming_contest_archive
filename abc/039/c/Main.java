import java.util.Scanner;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        String S = sc.next();
        String keys = "WBWBWWBWBWBW";
        String[] anses = {"Do", "x", "Re", "x", "Mi", "Fa",
                          "x", "So", "x", "La", "x", "Si"};
        for(int offset = 0; offset < keys.length(); ++offset) {
            boolean ok = true;
            for(int i = 0; i < S.length(); ++i) {
                if (S.charAt(i) != keys.charAt((offset + i) % keys.length())) {
                    ok = false;
                }
            }
            if (ok) {
                System.out.println(anses[offset]);
                return;
            }
        }
    }
}

