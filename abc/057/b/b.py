#!/usr/bin/env python3

N, M = [int(x) for x in input().split()]
ABs = []
for n in range(N):
    ABs.append([int(x) for x in input().split()])
CDs = []
for m in range(M):
    CDs.append([int(x) for x in input().split()])
for a, b in ABs:
    dists = [abs(a - c) + abs(b - d) for c, d in CDs]
    print(dists.index(min(dists)) + 1)
