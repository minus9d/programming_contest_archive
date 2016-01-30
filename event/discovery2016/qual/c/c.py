#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itertools


S = input()
K = int(input())

job = [1,2,3]

best = "zzzzz"
for jobs in itertools.product(job, repeat=K):
    s = S[:]
    for j in jobs:
        if j == 1:
            done = False
            for i in range(len(s)-1):
                if s[i] > s[i+1]:
                    s = s[:i] + s[i+1:]
                    done = True
                    break
            if not done:
                s = s[:-1]
        elif j == 2:
            for i in range(len(s)):
                if s[i] != 'a':
                    s = s[:i] + 'a' + s[i+1:]
                    break
        elif j == 3:
            s = 'a' + s
                
    best = min(best, s)
        
print(best)
    
