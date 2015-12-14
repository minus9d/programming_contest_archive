#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())

def zoro(n):
    s = str(n)
    for ch in s:
        if ch != s[0]:
            return False
    return True

n = 1
cnt = 0
while True:
    if zoro(n):
        cnt += 1
        if cnt == N:
            print(n)
            break
    n += 1
        

