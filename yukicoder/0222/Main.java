import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.regex.MatchResult;


public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
            
        String str = sc.next();

        Scanner s = new Scanner(str);
        s.findInLine("([+-]?\\d+)([+-])([+-]?\\d+)");
        MatchResult result = s.match();

        int n1 = Integer.parseInt(result.group(1));
        int n2 = Integer.parseInt(result.group(3));
        String sign = result.group(2);

        if (sign.equals("+")) {
            System.out.println(n1 - n2);
        }
        else {
            System.out.println(n1 + n2);
        }
    }
}

