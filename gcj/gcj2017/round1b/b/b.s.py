#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
R, G, Bいずれかが過半数を超えるときはIMPOSSIBLE
それ以外のときは、R, G, Bが連続しないよう、数の多いものから順番に使っていく
ただし、輪の最初と最後が同じになることを防ぐため、輪の最初に使った色に +0.1 して
この色が優先的に使われるようにする
"""

def validate(N, R, O, Y, G, B, V, ans):
    if len(ans) != N:
        print("error! len differs")
    elif 'RR' in ans or 'GG' in ans or 'BB' in ans:
        print("error! succ")
    elif ans.count('R') != R:
        print("error! r count")
    elif ans.count('G') != G:
        print("error! g count")
    elif ans.count('B') != B:
        print("error! b count")
    elif ans[0] == ans[-1]:
        print("error! first and last")
    else:
        print("ok")

def solve(N, R, O, Y, G, B, V):
    nums =  [R, O, Y, G, B, V]
    names = ['R', 'O', 'Y', 'G', 'B', 'V']
    mx = max(nums)
    if mx <= N // 2:
        pairs = list(zip(nums, names))
        ans = ''
        prev = 'z'
        for n in range(N):
            pairs.sort()
            pairs.reverse()
            for m in range(N):
                if pairs[m][1] != prev:
                    ans += pairs[m][1]
                    pairs[m] = (pairs[m][0]-1, pairs[m][1])
                    prev = pairs[m][1]
                    if n == 0:
                        pairs[m] = (pairs[m][0] + 0.1, pairs[m][1])
                    break
        # validate(N, R, O, Y, G, B, V, ans)
        print(ans)
    else:
        print("IMPOSSIBLE")

T = int(input())
for testcase in range(T):
    N, R, O, Y, G, B, V = map(int, input().split())
    print("Case #{}: ".format(testcase+1), end="")
    solve(N, R, O, Y, G, B, V)
