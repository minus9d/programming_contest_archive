#!/usr/bin/env python3
# -*- coding: utf-8 -*-

S = input()

for n in range(100, 2, -1):
    target = "o" * n + "kayama"
    # print(target)
    if n % 3 == 0:
        goal = "Ookayama"
    elif n % 3 == 1:
        goal = "okayama"
    else:
        goal = "Okayama"
    S = S.replace(target, goal)
        
print(S)
