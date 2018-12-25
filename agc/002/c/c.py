#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def solve():
    N,L = map(int,input().split())
    As = list(map(int,input().split()))
    for i in range(N-1):
        if As[i] + As[i+1] >= L:
            print("Possible")
            keep = i + 1
            for n in range(1,keep):
                print(n)
            for n in range(N-1, keep, -1):
                print(n)
            print(keep)
            return
    print("Impossible")
        
solve()

