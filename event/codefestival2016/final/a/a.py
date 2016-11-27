#!/usr/bin/env python3
# -*- coding: utf-8 -*-

H,W = map(int,input().split())
for h in range(H):
    words = input().split()
    for w, word in enumerate(words):
        if word == 'snuke':
            print('{}{}'.format(chr(ord('A')+w), h+1))
    
