#!/usr/bin/env python
# -*- coding: utf-8 -*-

(N,K)=map(int,input().split())

# python3では、map()はイテレータを返すようになった
Rs=list(map(int,input().split()))

Rs.sort()

rate=0
for i in range(N-K, N):
    rate = (rate + Rs[i]) / 2

print("%.7f" % rate)

