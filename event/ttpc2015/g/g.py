#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

def f(base, chars_copy, idx, s):
    if chars_copy[base] <= 0:
        return False
    chars_copy[base] -= 1
    chars_copy[base+1] += 1
    return dp(s, idx+1, tuple(chars_copy))


# s: 文字列
# idx: 今注目している文字列のindex
# chars: サイズ6のタプル
@functools.lru_cache(maxsize = None)
def dp(s, idx, chars):
    if idx == len(s):
        # print("chars:", chars)
        return sum(chars[:-1]) == 0
    
    ch = s[idx]
    chars_copy = list(chars)
    if ch == 't':
        chars_copy[0] += 1
        ans1 = dp(s, idx+1, tuple(chars_copy))
        chars_copy[0] -= 1

        ans2 = False
        if chars_copy[1] > 0:
            chars_copy[1] -= 1
            chars_copy[2] += 1
            ans2 = dp(s, idx+1, tuple(chars_copy))
        
        return ans1 or ans2
    elif ch == 'i':
        return f(0, chars_copy, idx, s)
    elif ch == 'e':
        return f(2, chars_copy, idx, s)
    elif ch == 'c':
        return f(3, chars_copy, idx, s)
    elif ch == 'h':
        return f(4, chars_copy, idx, s)
    
S = input()
l = tuple([0] * 6)
ans = dp(S, 0, l)
if ans:
    print("Yes")
else:
    print("No")


            
