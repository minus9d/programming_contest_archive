#!/usr/bin/env python
# -*- coding: utf-8 -*-


def getDir(deg, w):
    table = ["N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
             "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW",
             "N"]
    threshold = 1125
    index = 0
    increment = 2250

    deg *= 10
    if (w == 0):
        return "C"
    else:
        while 1:
            if deg < threshold:
                return table[index]
            else:
                threshold += increment
                index += 1
        
def getW(dis):
    tablex10 = [2, 15, 33, 54, 79, 107, 138, 171, 207, 244, 284, 326]

    mPerSx10 = round((dis + 1e-9) / 6)  # !! 

    for i, v in enumerate(tablex10):
        if mPerSx10 <= v:
            return i
    return len(tablex10)
    
                
(deg, dis) = map(int, input().split())

w = getW(dis)
dir = getDir(deg, w)
print (dir + " " + str(w))
