#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import collections
import queue

def simulate(N, K):
    arr = [1] + [0] * N + [1]

    for k in range(K):
        max_pos = -1
        max_d_l = -1
        max_d_r = -1
        for i in range(1, N + 1):
            if arr[i] == 1:
                continue
            dist_r = arr.index(1, i) - i - 1
            rev_i = len(arr) - i - 1
            dist_l = arr[::-1].index(1, rev_i) - rev_i - 1
#            print("dist_l, dist_r = ", dist_l, dist_r)
            if min(dist_l, dist_r) > min(max_d_l, max_d_r) or \
            min(dist_l, dist_r) == min(max_d_l, max_d_r) and \
            max(dist_l, dist_r) > max(max_d_l, max_d_r):
                max_d_l = dist_l
                max_d_r = dist_r
                max_pos = i
        arr[max_pos] = 1

    return tuple(reversed(sorted([max_d_l, max_d_r])))


def split_two(n):
    mn = mx = (n - 1) // 2
    if mn + mx < n - 1:
        mx += 1
    return (mx, mn)
    
def add_num(q, c, n, num):
    if n not in c:
        q.put(-n)
    c[n] += num

def fast(N, K):
    q = queue.PriorityQueue()
    q.put(-N)
    c = collections.Counter()
    c[N] = 1
    while K > 0:
        n = -q.get()
        num = c[n]
        del c[n]
        if num >= K:
            return split_two(n)
        else:
            K -= num
            mx, mn = split_two(n)
            if mx == mn and mx != 0:
                add_num(q, c, mx, num * 2)
            else:
                if mn != 0:
                    add_num(q, c, mn, num)
                add_num(q, c, mx, num)


# for n in range(1, 1001):
#     for k in range(1, n + 1):
#         ans1 = simulate(n, k)
#         ans2 = fast(n, k)
#         if ans1 != ans2:
#             print("error! n, k, sim, fast = ", n, k, ans1, ans2)
#             sys.exit(0)
#             break
#         else:
#             pass

def solve():
    N, K = map(int, input().split())
    print(" ".join(str(x) for x in fast(N, K)))

def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ": ", end="")
        solve()

main()
