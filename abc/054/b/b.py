#!/usr/bin/env python

N, M = map(int, input().split())
As = []
Bs = []

ret = 'No'
for n in range(N):
    As.append(input())
for m in range(M):
    Bs.append(input())

for i in range(N-M+1):
    for j in range(N-M+1):
        same = True
        for k in range(M):
            if As[i+k][j:j+M] != Bs[k]:
                same = False
                break
        if same:
            ret = 'Yes'
print(ret)
