#!/usr/bin/env python3
# -*- coding: utf-8 -*-

R,G,B = map(int, input().split())

# num: 色の数
# origin: 色が最初に置かれた座標
# left, 配置した色の左端の座標
def calcCost(num, origin, left):
    ret = 0
    while num > 0:
        ret += abs(left - origin)
        left += 1
        num -= 1
    return ret

costMin = int(1e9)
a = 0
# Rの左限でループ
for rLeft in range(-500, -95):
    for gLeft in range(rLeft+R, 55):
        for bLeft in range(gLeft+G, 345):
            a += 1

print(costMin)


