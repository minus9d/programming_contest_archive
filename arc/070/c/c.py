#!/usr/bin/env python3

X = int(input())

n = 1
s = 0
while True:
    s += n
    if s >= X:
        print(n)
        break
    else:
        n += 1
