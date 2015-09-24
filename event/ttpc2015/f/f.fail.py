#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# def bf(a):
#     ret = -1
#     best_x = -1
#     for x in range(a, a + 1000):
#         sub = x - a
#         s1 = (str(a))[::-1]
#         s2 = (str(x))[::-1]
#         s3 = (str(sub))[::-1]
#         tmp = 0
#         for c1,c2,c3 in zip(s1,s2,s3):
#             if c1 == c2 == c3:
#                 tmp += 1
#         if tmp > ret:
#             ret = tmp
#             best_x = x

#     # print("best x:", best_x)
#     return ret


def solve(a):
    if a < 10:
        return 0
    if a % 10 == 0:
        return 1 + solve(a // 10)

    s = str(a)
    s = list(map(int,s[::-1]))
    
    t = 0
    ans = 0
    for i in range(len(s)):
        if s[i] == 0 and t == 0:
            ans += 1
        else:
            if s[i] == 9:
                if t != 0:
                    ans += 1
                    t = 1
            if i != len(s)-1 and s[i+1] == 9:
                if s[i] + t + 9 >= 10:
                    t = 1
                else:
                    t = 0
    return ans
        
# verify    
# for a in range(1,1000):
#     ans = bf(a)
#     myans = solve(a)
#     if ans != myans:
#         print(a, ": not match.. ans,myans = ", ans, ",", myans)

A = int(input())
print(solve(A))
