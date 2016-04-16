#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import Counter

def solve():
    N = int(input())
    m = Counter()
    for _ in range(N * 2 - 1):
        m.update(input().split())
    return ' '.join(sorted([str(x) for x in m if m[x] % 2], key=int))

def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ":", solve())

main()

