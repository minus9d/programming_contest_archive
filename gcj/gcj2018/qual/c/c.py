#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import random
import re
import string
import sys

write_num = 0
def write_query(query):
    global write_num
    print(query)
    sys.stdout.flush()
    write_num += 1
    # sys.stderr.write("write_num: {}\n".format(write_num))
    if write_num == 1000:
        sys.exit(0)

def solve():
    global write_num
    write_num = 0

    A = int(input())
    
    if A == 20:
        H = 4
        W = 5
    elif A == 200:
        H = 14
        W = 15
    else:
        SIZE = 3
        while SIZE * SIZE < A:
            SIZE += 1
        H = W = SIZE

    cells = [[0 for _ in range(1001)] for _ in range(1001)]

    # sys.stderr("{}\n".format(cells))
    query = "2 2"
    write_query(query)

    # the cell first prepared will be left-top cell
    res = input()
    h, w = map(int, res.split())
    sys.stderr.flush()
    cells[h][w] = 1
    lefttop_h = h
    lefttop_w = w

    # "target" means the cell which should be prepared next
    for target_h in range(lefttop_h, lefttop_h + H):
        for target_w in range(lefttop_w, lefttop_w + W):
            # sys.stderr.write("target: {}, {}\n".format(target_h, target_w))
            # skip if the target cell is already prepared
            if cells[target_h][target_w]:
                continue

            query_h = min(target_h + 1, lefttop_h + H - 2)
            query_w = min(target_w + 1, lefttop_w + W - 2)

            while True:
                query = "{} {}".format(query_h, query_w)
                write_query(query)
                res = input()
                res_h, res_w = map(int, res.split())
                # sys.stderr.write("======\n")
                # sys.stderr.write("target: {} {}\n".format(target_h, target_w))
                # sys.stderr.write("query: {}\n".format(query))
                # sys.stderr.write("res: {}\n".format(res))

                # complete
                if (res_h, res_w) == (0, 0):
                    sys.stderr.write("write_num: {}\n".format(write_num))
                    return

                cells[res_h][res_w] = 1
                if (res_h, res_w) == (target_h, target_w):
                    break


T = int(input())
for testcase in range(T):
    solve()
