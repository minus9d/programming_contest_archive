#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,A,B = map(int,input().split())
S = input()

passed = 0
overseas = 0
for ch in S:
    if ch == 'a':
        if passed < A + B:
            print('Yes')
            passed += 1
        else:
            print('No')
    elif ch == 'b':
        if passed < A + B and overseas < B:
            print('Yes')
            passed += 1
            overseas += 1
        else:
            print('No')
    else:
        print('No')

