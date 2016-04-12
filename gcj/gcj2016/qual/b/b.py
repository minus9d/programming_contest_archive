#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def solve(s):
    # ++---+-+ -> +-+-+
    s2 = "z"
    for ch in s:
        if ch != s2[-1]:
            s2 += ch
    s2 = s2[1:]

    # +-+-+ -> +-+-
    if s2[-1] == '+':
        s2 = s2[:-1]

    return len(s2)

T=int(input())
for testcase in range(T):
    s = input()
    ans = solve(s)
    print("Case #{}: {}".format(testcase+1, ans))
