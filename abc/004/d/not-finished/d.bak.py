#!/usr/bin/env python3
# -*- coding: utf-8 -*-

R,G,B = map(int, input().split())

# 色の数がnum, 基準位置からoffsetずれた場合の移動量
# e.g. num = 5, offset = -1
#   o o o o o
#     |
#    基準位置
def calcCost(num, offset):
    ret = 0
    while num > 0:
        ret += abs(offset)
        offset -= 1
        num -= 1
    return ret

# Gの左限でループ
costMin = int(1e9)
for gLeft in range(-G-500, G+500):
    gRight = gLeft + G - 1
    cost = calcCost(G, gRight)
    print("G = [", gLeft, ", ", gRight, "]")
    
    if R > 0:
        # RはGに接するか？
        normalRRight = -100 + (R-1)//2
        if normalRRight > gLeft:
            cost += calcCost(R, gLeft-G+100)
            print("R = [", 0, ", ", gLeft-1, "]")
        else:
            cost += calcCost(R, (R-1)//2)
    if B > 0:
        # BはGに接するか？
        normalBLeft = 100 + (B-1)//2
        if normalBLeft < gRight:
            cost += calcCost(B, gRight + 1 - 100)
        else:
            cost += calcCost(B, (B-1)//2)
    costMin = min(cost, costMin)

print(costMin)


