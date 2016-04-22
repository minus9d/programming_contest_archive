#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import string

def subt(pos, n):
    """座標posで移動量nのとき、0方面に近づけた後の座標と、移動方向を返す"""
    if pos > 0:
        return pos - n, n
    else:
        return pos + n, -n

def solve2(x,y):
    x_init = x
    y_init = y

    # x, yに行くために絶対必要な手数を求める
    # 証明はできていないが、これが最小の手数になる
    s = 0
    n = 1
    while True:
        s += n
        if s >= (x + y) and (s % 2) == ((x + y) % 2):
            break
        n += 1

    # 移動量が大きな手数の方から順に消費し、
    # x, yのうち絶対値大きい方を0に近づける
    x_elements = [] # debug用
    y_elements = [] # debug用
    directions = ""
    for i in range(n, 0, -1):
        if abs(x) > abs(y):
            x, i2 = subt(x, i)
            x_elements.append(i2)
            if i2 > 0:
                directions += "E"
            else:
                directions += "W"
        else:
            y, i2 = subt(y, i)
            y_elements.append(i2)
            if i2 > 0:
                directions += "N"
            else:
                directions += "S"
        #print("i, x, y, lastchar = ", i, x, y, directions[-1])

    # validation
    if sum(x_elements) != x_init or sum(y_elements) != y_init:
        print("error!")
        sys.exit()
    
    return directions[::-1]
            

def solve():
    X,Y = map(int, input().split())
    directions = solve2(abs(X), abs(Y))

    if X < 0:
        directions = directions.translate(str.maketrans('EW', 'WE'))
    if Y < 0:
        directions = directions.translate(str.maketrans('NS', 'SN'))

    # validation
    n = 1
    x = y = 0
    for ch in directions:
        if ch == "N":
            y += n
        elif ch == "S":
            y -= n
        elif ch == "E":
            x += n
        elif ch == "W":
            x -= n
        n += 1
    if x != X or y != Y:
        print("error!")

    return directions

def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ":", solve())

main()

