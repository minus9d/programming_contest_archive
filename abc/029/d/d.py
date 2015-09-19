#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 数字nの各桁(digit)ごとに、1からnまでの間に、1が登場する回数を数える
# (i)digit = 0の場合：コーナーケースで特別扱い
# (ii)それ以外の場合(例えばdigit = 2)
# n = 2182のとき
#    [2100, 2182]で1が現れた分:  83
#    [100, 2100)で1が現れた分:  (2100 - 100) / 10
# n = 2354のとき
#    [2100, 2199]で1が現れた分:  100
#    [100, 2100)で1が現れた分:  (2100 - 100) / 10
def f(n, digit):
    s = str(n)
    size = len(s)
    ret = 0

    # コーナーケース
    if digit == 0:
        return ((n+9) // 10)

    base = int('1' + '0' * (digit))

    ans = 0
    if s[size-digit-1] == '0':
        return f(n - base, digit)

    new_n = int(s[:size-digit-1] + '1' + '0' * (digit))
        
    if s[size-digit-1] == '1':
        ans = n - new_n + 1
    else:
        ans = base

    # print("n,digit,new_n,base,temp_ans = ", n,digit, new_n, base, ans)
    ans += (new_n - base) // 10
    return ans


def bf(n):
    ret = 0
    for i in range(n+1):
        s = str(i)
        ret += s.count("1")
    return ret

def solve(N):
    ans = 0
    for n in range(len(str(N))):
        t = f(N,n)
        # print("f(",N,",",n,") = ", t)
        ans += t
    return ans

N = int(input())
print(solve(N))

for n in range(100,1000):
#for n in range(1000):
    a1 = bf(n)
    a2 = solve(n)
    # print("n, a1 = ", n, a1)
    if a1 != a2:
        print("not match: n, bf, myans = ", n, a1, a2)
        break



