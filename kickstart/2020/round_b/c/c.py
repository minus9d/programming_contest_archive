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


def parse_one_command(one_command):
    """
    "N" -> (0, -1)
    "S" -> (0, 1)
    "E" -> (1, 0)
    "W" -> (-1, 0)
    """
    if one_command == "N": return (0, -1)
    elif one_command == "S": return (0, 1)
    elif one_command == "E": return (1, 0)
    elif one_command == "W": return (-1, 0)
    raise ValueError

def mul_tuple(num, t):
    return (t[0] * num, t[1] * num)

def add_tuple(t1, t2):
    return (t1[0] + t2[0], t1[1] + t2[1])

def find_close_par(command, i):
    num = 0
    while True:
        ch = command[i]
        if ch == "(":
            num += 1
        elif ch == ")":
            num -= 1
            if num == 0:
                return i
        i += 1

def parse(command):
    """
    "3(S)" -> (0, 3)
    """

    ret = (0, 0)

    i = 0
    while i < len(command):

        ch = command[i]
        if "2" <= ch <= "9":
            mul = ord(ch) - ord("0")

            # find index of ")" from ch(xxx)
            close_i = find_close_par(command, i + 1)
            inner_command = command[i + 2: close_i]
            parsed = parse(inner_command)
            ret = add_tuple(ret, mul_tuple(mul, parsed))
            i = close_i + 1

        elif ch in "NEWS":
            ret = add_tuple(ret, parse_one_command(ch))
            i += 1

        else:
            raise ValueError
    return ret


def solve():
    command = input()
    res = parse(command)
    final_loc = tuple(e % 1000000000 + 1 for e in res)
    print(*final_loc)

T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
