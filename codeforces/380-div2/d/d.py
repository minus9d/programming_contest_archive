#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N,A,B,K = map(int,input().split())
s = input()

fst = -1
buf = ''
divs = []
for i, ch in enumerate(s):
    if ch == '1':
        if buf != '':
            divs.append((buf, fst))
            buf, fst = '', -1
        else:
            pass
    else:
        buf += ch
        if fst == -1:
            fst = i
if buf != '':
    divs.append((buf, fst))

hidden_max = 0
for buf, fst in divs:
    hidden_max += len(buf) // B

must = hidden_max - A + 1
print(must)

ans = []
for buf, fst in divs:
    length = len(buf)
    pos = 0
    while length >= B and must > 0:
        ans.append(pos + fst + B)
        pos += B
        length -= B
        must -= 1
    if must == 0:
        break
print(*ans)
