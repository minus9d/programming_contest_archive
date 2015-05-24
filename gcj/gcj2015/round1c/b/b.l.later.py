#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from itertools import *

def solve():
    K,L,S = map(int,input().split())
    keys = input()
    target = input()

    # targetを1つ並べられる確率
    p = 1.0
    for ch in target:
        p *= keys.count(ch) / len(keys)

    # 期待値の線形性を使う
    expect = (S - len(target) + 1) * p

    # slide := targetを重ねられる最小移動数
    slide = len(target)
    for i in range(1, len(target)):
        if target.startswith( target[i:] ):
            slide = i
            break
    # 最大に並べられる数
    mx = 1 + (S - len(target)) // slide

    # 期待値が0のときに気をつける
    if expect == 0:
        return 0
    else:
        return mx - expect

def main():
    T = int(input())
    for t in range(T):
        a = solve()
        print ("Case #{0}: {1:.10f}".format(t+1, a))
        #print ("Case #" + str(t+1) + ":", a)

main()

