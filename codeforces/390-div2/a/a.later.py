#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N = int(input())
As = list(map(int,input().split()))
if min(As) == max(As) == 0:
    print("NO")
else:
    print("YES")
    if sum(As) != 0:
        print("1")
        print("{} {}".format(1,N))
    else:
        Bs = []
        i = 0
        while sum(Bs) == 0:
            Bs.append(As[i])
            i += 1
        print("2")
        print(1, i)
        print(i+1, N)

        

