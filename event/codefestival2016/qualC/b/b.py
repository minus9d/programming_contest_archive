#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import heapq

K,T = map(int,input().split())
As = list(map(int,input().split()))
mx = max(As)
others = K - mx
print(max(mx - 1 - others, 0))
