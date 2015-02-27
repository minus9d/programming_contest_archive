#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re

def getArea(ax, ay, bx, by):
    return abs( ax * by - ay * bx ) / 2.0


(xa,ya,xb,yb,xc,yc) = map(int, input().split())
print ( getArea( xa - xc, ya - yc, xb - xc, yb - yc ) );
