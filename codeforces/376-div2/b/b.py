#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())

def solve2(stirng):
    nums = list(map(int, string.split()))
    
    odd = 0
    for num in nums:
        if odd:
            num -= 1
            odd = 0
            if num < 0:
                return "NO"

        if num % 2:
            odd = 1
            
    if odd:
        return "NO"
    else:
        return "YES"


string = input()
print(solve2(string))
