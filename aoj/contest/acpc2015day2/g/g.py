#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# それぞれの文字列について、文字の出現頻度が高い順に並べる
# e.g.
#   s1 = "yyyzzccb" -> [3, 2, 2, 1]
#   s2 = "aabbcdef" -> [2, 2, 1, 1, 1, 1]
# 同じ順位の文字同士をマッチングさせる
# 置換回数は、((3-2) + (2-2) + (2-1) + (1-1) + 1 + 1) / 2 = 2

from collections import defaultdict

N = int(input())
s1 = input()
s2 = input()

# 文字列から頻度回数を取り出す
# e.g. s: "yyyzzccb"
#      ret: [3, 2, 2, 1] 
def make_appears(s):
    chars = list(map(ord, s))
    hist = defaultdict(int)
    for ch in chars:
        hist[ch] += 1
    appears = list(hist.values())
    appears.sort()
    appears.reverse()
    return appears
    
appears1 = make_appears(s1)
appears2 = make_appears(s2)

ans = 0
for i, j in zip(appears1, appears2):
    ans += abs(i - j)

shorter = min(len(appears1), len(appears2))
ans += sum(appears1[shorter:]) + sum(appears2[shorter:])

print(ans//2)
