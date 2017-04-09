import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;

public class C
{
    Scanner sc = new Scanner(System.in);

    Long[] split_two(Long n) {
        Long mn;
        Long mx;
        mn = mx = (n - 1) / 2;
        if (mn + mx < n - 1) {
            mx += 1L;
        }
        Long ret[] = {mx, mn};
        return ret;
    }

    void add_num(PriorityQueue<Long> queue, Map<Long, Long> map,
                 Long n, Long num) {
        if (map.get(n) == null) {
            queue.add(-n);
            map.put(n, num);
        }
        else {
            map.put(n, map.get(n) + num);
        }
    }

    void solve() {
        PriorityQueue<Long> queue = new PriorityQueue<Long>(10); 
        Map<Long, Long> map = new HashMap<Long, Long>();
        Long N = sc.nextLong();
        Long K = sc.nextLong();
        queue.add(-N);
        map.put(N, 1L);
        
        while (K > 0) {
            Long n = -queue.remove();
            Long num = map.get(n);
            map.remove(n);
            if (num >= K) {
                Long[] mxmn = split_two(n);
                System.out.printf("%d %d", mxmn[0], mxmn[1]);
                return;
            }
            else {
                K -= num;
                Long[] mxmn = split_two(n);
                Long mx = mxmn[0];
                Long mn = mxmn[1];
                if (mx == mn && mx != 0) {
                    add_num(queue, map, mx, num * 2);
                }
                else {
                    if (mn != 0) {
                        add_num(queue, map, mn, num);
                    }
                    add_num(queue, map, mx, num);
                }
            }
        }
   }

    void run() {
        int T = sc.nextInt();
        for (int t = 1; t <= T; ++t) {
            System.out.printf("Case #%d: ", t);
            solve();
            System.out.printf("\n");
            System.out.flush();
        }
    }

    public static void main(String[] args) {
        new C().run();
    }
}
