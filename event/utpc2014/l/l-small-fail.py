#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itertools

input_str = input()
prms = set()
for ch in input_str:
    if ch != '*' and ch != '+':
        prms.add(ch)

char_to_idx = {}
idx = 0
for p in prms:
    char_to_idx[p] = idx
    idx += 1

    
def make_lambda(input_str, prms):
    ret = "lambda "
    ret += ",".join(list(prms))
    ret += ":" + input_str
    return ret

eval_func = eval(make_lambda(input_str, prms))

mx = 10000
ret = 0
for comb in range(1 << len(prms)):
    sign = [ (1 if comb & (1 << j) else -1) for j in range(len(prms)) ]
    result = eval_func(*sign)

    if result < mx:
        mx = result
        ret = 1
    elif result == mx:
        ret += 1
print(ret)
    

