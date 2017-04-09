#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import collections
import queue
from itertools import *
import numpy as np

def count_element(arr, char):
    return np.count_nonzero( arr == char )

def is_valid_plus(cells, N):
    for i in range(N):
        plus = count_element(cells[i], '+')
        cross = count_element(cells[i], 'x')
        circle = count_element(cells[i], 'o')
        dot = count_element(cells[i], '.')
        filled = N - dot
        if filled >= 2 and plus == 0:
            return False
    return True

def is_valid_cross(cells, N):
    # print("===")
    # print("cells:")
    # print(cells)
    for i in range(0, N):
        arr = np.array([])
        for j in range(N - i):
            arr = np.append(arr, cells[i + j][j])
        # print("arr:", arr)
        plus = count_element(arr, '+')
        cross = count_element(arr, 'x')
        circle = count_element(arr, 'o')
        dot = count_element(arr, '.')
        filled = len(arr) - dot
        if filled >= 2 and cross == 0:
            return False
    return True

def calc_score(cells, N):
    score = 0
    for i in range(N):
        score += count_element(cells[i], '+')
        score += count_element(cells[i], 'x')
        score += 2 * count_element(cells[i], 'o')
    return score

def is_valid(cells, N):
    if not is_valid_plus(cells, N):
        return False

    cells = cells.transpose((1, 0))
    if not is_valid_plus(cells, N):
        return False

    if not is_valid_cross(cells, N):
        return False
    cells = cells.transpose((1, 0))
    if not is_valid_cross(cells, N):
        return False
    cells = cells.transpose((1, 0))

    cells = cells[:, ::-1]
    if not is_valid_cross(cells, N):
        return False
    cells = cells.transpose((1, 0))
    if not is_valid_cross(cells, N):
        return False

    return True

def simulate(N):
    mx_score = 0
    mx_cells = None
    for comb in product(['o', 'x', '+', '.'], repeat = N ** 2):
        cells = np.array(comb).reshape((N, -1))
        if is_valid(cells, N):
            print("=====")
            print("valid")
            print(cells)
            score = calc_score(cells, N)
            print(score)
            if score > mx_score:
                mx_score = score
                mx_cells = cells
        else:
            pass
            # print("not valid")
            # print(cells)
            # print()
    print("mx score:", mx_score)
    print(mx_cells)

    mx_cells = np.array([['o', 'x', '+'],
                         ['+', 'x', 'x'],
                         ['o', '+', 'o'],])
    validity = is_valid(mx_cells, N)
    print("validity:", validity)


simulate(4)

def solve():
    pass
    # N, K = map(int, input().split())
    # print(fast(N, K))

def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ": ", end="")
        solve()

main()
