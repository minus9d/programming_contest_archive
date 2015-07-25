#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,M = map(int,input().split())
threads = [(x,x) for x in range(N)]
for m in range(M):
    a = int(input())
    threads[a-1] = (-m-1,a-1)
threads.sort()
for t in threads:
    print(t[1]+1)


