#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def solve(n):
    seen = set()
    cnt = 1
    ans = None
    while True:
        val = n * cnt
        seen.update( str(val) )
        # print("val, seen:", val, seen)

        if len(seen) == 10:
            ans = val
            break
        if cnt == 1000000:
            ans = "INSOMNIA"
            break

        cnt += 1

    return ans

# for n in range(int(1e6)):
#     ans = solve(n)
#     print("n, ans: ", n, ans)

T=int(input())
for testcase in range(T):
    n = int(input())
    ans = solve(n)
    print("Case #{}: {}".format(testcase+1, ans))
