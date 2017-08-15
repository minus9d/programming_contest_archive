#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Smallは一本道。各街で馬を乗り換えるか否かの2択をDPで行う。
本番では最悪値の取り方が不十分で1WA
"""

def solve():
    N, Q = map(int, input().split())
    Es = []
    Ss = []
    for n in range(N):
        e, s = map(int, input().split())
        Es.append(e)
        Ss.append(s)
    Ds = []
    for n in range(N):
        Ds.append(list(map(int, input().split())))

    anses = []
    for q in range(Q):
        u, v = map(int, input().split())
        u -= 1
        v -= 1

        # small only

        # [pos][horse idx] = (time, energy)
        dp = [[None] * N for i in range(N + 1)]
        for i in range(N):
            if i == 0:
                # dp[1][0] = (dist / Ss[0], Es[0] - dist)
                dp[0][0] = (0, Es[0])
            else:
                dist = Ds[i-1][i]
                for n in range(N-1):
                    if dp[i-1][n] is not None:
                        p_time, p_dist = dp[i-1][n]
                        if p_dist < dist:
                            continue
                        n_time = p_time + dist / Ss[n]
                        dp[i][n] = (n_time, p_dist - dist)

                        if dp[i][i] is None:
                            dp[i][i] = (n_time, Es[i])
                        else:
                            dp[i][i] = (min(dp[i][i][0], n_time), Es[i])

        ans = 1e19
        for n in range(N):
            if dp[N-1][n] is not None:
                ans = min(ans, dp[N-1][n][0])
        anses.append(ans)
        # print(dp)
    for i in range(len(anses)):
        print("", "{:.12f}".format(ans), end="")
    print()


T = int(input())
for testcase in range(T):
    print("Case #{}:".format(testcase+1), end="")
    solve()
