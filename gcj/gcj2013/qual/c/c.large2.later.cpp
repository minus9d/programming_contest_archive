#!/bin/env python
# -*- coding: utf-8 -*-

# large-2解くのに5分35秒かかった


# aはpalindrrome.
# a * aの計算の過程で、どの桁にも繰り上がりがなければ、
# a * aもpalindrome.
def check(a):
    N = len(a)
    b = [0] * (2*N-1)
    for i in xrange(0, N):
        for j in xrange(0, N):
            b[i+j] += a[i] * a[j]
    for i in xrange(0, 2*N-1):
        if b[i] >= 10:
            return False
    return True

# 
def dfs(N, a, L, R):
    # print "N, a, L, R = ", N, a, L, R
    if (not check(a)):
        return
    if L >= R:
        good.append( N * N )
        return
    for i in xrange(0, 4):
        if (i != 0 or L != 0):
            M = N
            M += i * ten[L]
            if R-1 != L:
                M += i * ten[R-1]
            a[L] = a[R-1] = i
            dfs(M, a, L+1, R-1)
            a[L] = a[R-1] = 0

##############
# ここから準備
##############

# fair and squareな数を記録
good = []

# 1, 10, 100, ...
ten = []
ten.append(1)
for i in xrange(1,110):
    ten.append( ten[-1]*10 )

# iは桁数
for i in xrange(1,51):
    a = [0] * i
    dfs(0, a, 0, i);


##############
# ここまで準備
##############

T = int(raw_input())
for i in range(T):
    v = map(int, raw_input().split())
    A = v[0]
    B = v[1]
    ans = 0
    for g in good:
        if A <= g <= B:
            ans += 1
    
    print "Case #%d:" % (i + 1), ans 
    


