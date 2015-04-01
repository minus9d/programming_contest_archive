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

# Gの左限でループ
costMin = int(1e9)
for gLeft in range(-500, +500):
    gRight = gLeft + G - 1
    cost = calcCost(G, 0, gLeft)
    #print()
    #print("G = [", gLeft, ", ", gRight, "]")
    
    if R > 0:
        # RはGに接するか？
        normalRRight = -100 + (R-1)//2
        if normalRRight > gLeft:
            rRight = gLeft - 1
            rLeft = rRight - R + 1
            #print("R = [", rLeft, ", ", rRight, "]")
            cost += calcCost(R, -100, rLeft)
        else:
            #print("R = yama")
            cost += calcCost(R, -100, -100-((R-1)//2))
    if B > 0:
        # BはGに接するか？
        normalBLeft = 100 + (B-1)//2
        if normalBLeft < gRight:
            bLeft = gRight + 1
            bRight = bLeft + B - 1
            #print("B = [", bLeft, ", ", bRight, "]")
            cost += calcCost(B, 100, gLeft)
        else:
            #print("B = yama")
            cost += calcCost(B, 100, 100-(B-1)//2)
    #print("cost = ", cost)
    costMin = min(cost, costMin)

print(costMin)


