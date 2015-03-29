#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from decimal import *

(x,y) = map(Decimal, input().split())

x_int = int(x.to_integral_exact(rounding=ROUND_DOWN))
y_int = int(y.to_integral_exact(rounding=ROUND_DOWN))

x_float = int((x - x_int) * 1000)
y_float = int((y - y_int) * 1000)

# Decimalを使うと-0となりうる対策
def safe(num):
    if num == 0:
        return 0
    else:
        return num


if x_float == 0 and y_float == 0:
    print (safe(x_int), safe(y_int), safe(x_int+1), safe(y_int))
    print (safe(x_int), safe(y_int), safe(x_int), safe(y_int+1))

elif x_float == 0:

    # 1つ目の直線
    # 正方形の右下と(x,y)を結ぶ
    x2 = x_int + 1
    y2 = y_int
    x3 = x2 + int((x - x2) * 1000)
    y3 = y2 + int((y - y2) * 1000)
    print(safe(x2), safe(y2), safe(x3), safe(y3))

    # 2つ目の直線
    print(x_int, 0, x_int, 1)

else:

    # 1つ目の直線
    # 正方形の左下と(x,y)を結ぶ
    x1 = x_int + x_float
    y1 = y_int + y_float
    print(safe(x_int), safe(y_int), safe(x1), safe(y1))

    # 2つ目の直線
    # 正方形の左上と(x,y)を結ぶ
    x2 = x_int
    y2 = y_int + 1
    x3 = x2 + int((x - x2) * 1000)
    y3 = y2 + int((y - y2) * 1000)
    print(safe(x2), safe(y2), safe(x3), safe(y3))
