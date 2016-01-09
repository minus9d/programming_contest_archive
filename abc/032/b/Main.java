import java.util.Scanner;
import java.util.Set;
import java.util.HashSet;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        String s = sc.next();
        int k = sc.nextInt();
        int len = s.length();
        Set<String> seen = new HashSet<>();
        
        for(int i = 0; i < len - k + 1; ++i) {
            String substr = s.substring(i, i + k);
            seen.add(substr);
        }
        System.out.println(seen.size());
    }
}

