#!/usr/bin/env python3
# -*- coding: utf-8 -*-
S = input()

first_ = True

num = 0
pos = 1
while len(S) >= 3:
    ok = False
    for i in range(pos, len(S)-1):
        if S[i-1] == S[i+1]:
            continue
        else:
            S = S[:i] + S[i+1:]
            ok = True
            num += 1
            break
    if not ok:
        break

# print("num = ", num)
if num % 2 == 1:
    print('First')
else:
    print('Second')

