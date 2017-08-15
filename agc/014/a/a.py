#!/usr/bin/env python3
# -*- coding: utf-8 -*-
A,B,C = map(int, input().split())

cnt = 0
while A % 2 == B % 2 == C % 2 == 0:
    cnt += 1
    A, B, C = B // 2 + C // 2, A // 2 + C // 2, A //2 + B // 2
    if cnt == int(1e6):
        break
if cnt == 1e6:
    print(-1)
else:
    print(cnt)
