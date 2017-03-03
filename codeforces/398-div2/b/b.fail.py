#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import *

def solve(ts, tf, need_t, n, times):
    times = Counter(times)
    if n == 0:
        return ts
    else:

        # shortest_wait_time = ts - (times[0] - 1)
        # ans_time = times[0] - 1
        # available_time = ts

        shortest_wait_time = 1e15
        ans_time = -1
        available_time = None

        for i, t in enumerate(times.keys()):
            people_num = times[t]
            # the first one
            if i == 0 and t != 0:
                shortest_wait_time = ts - (t - 1)
                ans_time = t - 1

                available_time = ts + need_t * people_num

            elif i == 0 and t == 0:
                shortest_wait_time = ts + need_t * people_num
                ans_time = 0

                available_time = ts + need_t * people_num

            else:
                wait_time = max(0, available_time - (t - 1))
                print("at time {}: avail_t = {}, wait_t = {}".format(t-1, available_time, wait_time))
                if wait_time < shortest_wait_time:
                    shortest_wait_time = wait_time
                    ans_time = t - 1
                    # print("updated! current ans_time = ", ans_time)

                available_time = max(t, available_time) + need_t * people_num
                print("at time {}: avail_t = {}        ".format(t, available_time))
    
        # the last one
        if available_time <= tf - 1:
            ans_time = available_time

        return ans_time

def main():
    ts, tf, need_t = map(int, input().split())
    n = int(input())
    if n > 0:
        times = list(map(int, input().split()))
        times.sort()
    else:
        times = []
    ret = solve(ts, tf, need_t, n, times)
    print(ret)


if __name__ == '__main__':
    # print(solve(10, 100, 2, 0, []))  # 10
    # print(solve(10, 100, 10, 2, [10, 20])) # 30
    # print(solve(0, 10, 3, 3, [0, 3, 6])) # 9
    # print(solve(0, 10, 1, 4, [0, 0, 0, 0])) # 4
    # print(solve(0, 10, 2, 4, [0, 0, 0, 0])) # 8
    # print(solve(0, 10, 2, 4, [0, 3, 5, 6])) # 2, 9 are ok
    # print(solve(0, 11, 2, 5, [0, 0, 0, 0, 0])) # 10
    # print(solve(1, 12, 4, 5, [0, 0, 0, 0, 0])) # 0
    # print(solve(1, 1000000, 100, 5, [0, 0, 0, 0, 0, 9000]))
    main()
