#!/usr/bin/env python
# -*- coding: utf-8 -*-

(N,M) = map(int, input().split())

dict = {}

for m in range(M):
    (num1, num2) = map(int, input().split())
    num1 -= 1
    num2 -= 1
    if not num1 in dict:
        dict[num1] = {}
    dict[num1][num2] = 1

    if not num2 in dict:
        dict[num2] = {}
    dict[num2][num1] = 1

ret = 0
for i in (range(1<<N)):
    list = []
    for j in (range(N)):
        if ( i & (1<<j) ):
            list.append(j)

    ok = True
    for j in list:
        for k in list:
            if (j == k):
                continue
            if not(j in dict and k in dict[j]):
                ok = False
    if ok:
       ret = max(ret, len(list))
print (ret)

