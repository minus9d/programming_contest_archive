#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N = int(input())
As = list(map(int, input().split()))

def solve(As, first_target):
    ret = 0
    for i, a in enumerate(As):
        if i == 0:
            ret += abs(a - first_target)
            prev_sum = first_target
        else:
            curr_sum = prev_sum + a
            if prev_sum > 0 and curr_sum >= 0:
                ret += abs(curr_sum - (-1))
                curr_sum = -1
            elif prev_sum < 0 and curr_sum <= 0:
                ret += abs(curr_sum - 1)
                curr_sum = 1
            prev_sum = curr_sum
#            print("i, a, ret, curr_sum  = ", i, a, ret, curr_sum)
    return ret

ans1 = solve(As, 1)
ans2 = solve(As, -1)
ans3 = solve(As, As[0])
print(min(ans1, ans2, ans3))
