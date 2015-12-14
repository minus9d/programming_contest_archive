#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def Awin():
    N = int(input())
    A, B = map(int,input().split())

    if A == B:
        if N % (A + 1) == 0:
            return False
        else:
            return True
    else:
        if A > B:
            return True
        else:
            if N <= A:
                return True
            else:
                return False

ans = Awin()
if ans:
    print("Takahashi")
else:
    print("Aoki")

            
        
