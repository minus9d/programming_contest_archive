#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# west:
#   1 2 2 3 3 3 4 4 4 4 ...
# north:
#   n n+(n-1) n+(n-1)+(n-2) ...  n+(n-1)+...+1
# from top:
#   n n+(n-1) n+(n-1)+(n-2) ...  n+(n-1)+...+1

N = int(input())

def from_west(k):
    sum = 0
    v = 1
    while v <= N:
        sum += v
        if k <= sum:
            return v
        v += 1
    return 0

print(from_k(1))
print(from_k(2))
print(from_k(3))

def from_south(k):
    

print(from_k(1000000000))

