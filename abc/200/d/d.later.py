#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import copy
import sys

N = int(input())
As = list(map(int, input().split()))

def print_ans(arr1, arr2):
    def print_line(arr):
        arr = [len(arr)] + list(arr)
        print(*arr)
    print("Yes")
    print_line(arr1)
    print_line(arr2)
    
# {200の剰余: [index]}
# {0: []}を入れるとややこしくなるので入れない
val_to_arr = {}

for i, a in enumerate(As):
    a %= 200

    val_to_arr_copied = copy.deepcopy(val_to_arr)
    for val, arr in list(val_to_arr_copied.items()) + [(0, [])]:

        arr2 = arr + [i + 1]
        val2 = (val + a) % 200

        # 条件を満たすものを見つけたら終了
        if val2 in val_to_arr and arr2 and val_to_arr[val2] and val_to_arr[val2] != arr2:
            print_ans(val_to_arr[val2], arr2)
            sys.exit(0)
        if arr2:
            val_to_arr[val2] = arr2

print("No")
