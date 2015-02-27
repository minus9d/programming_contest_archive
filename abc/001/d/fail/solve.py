#!/usr/bin/env python
# -*- coding: utf-8 -*-

def find(x):
    if par[x] == x:
        return x
    else:
        par[x] = find(par[x])
        return par[x]

def same(x, y):
    return find(x) == find(y)

def unite(x, y):
    x = find(x)
    y = find(y)
    if (x == y):
        return
    par[x] = y

# union find 準備
vNum = 2400//5+1
par = [0] * vNum
for i in range(vNum):
    par[i] = i

seen = {}
    
N = int(input())
for i in range(0, N):
    (start, end) = map(int, input().split('-'))
    start -= (start % 5)
    end += (5 - (end % 5)) % 5

    for i in range(start, end+1, 5):
        seen[ i//5 ] = True # // は Cの/と同じ


isContinue = False
start = 0
end = 0
for i in range(0, 2400//5+1):
    if i in seen:
        if not isContinue:
            start = i
    else:
        if isContinue:
            isContinue = False
            end = i - 1
            print ("%04d-%04d" % (start, end))
if isContinue:
    print ("%04d-%04d" % (start, 2400))
