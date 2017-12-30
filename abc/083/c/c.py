#!/usr/bin/env python3

N = int(input())
CSF = []
for n in range(N-1):
    s = input()
    CSF.append([int(x) for x in s.split()])

for j in range(N - 1):
    time = 0
    for i in range(N - 1 - j):
        c, s, f = CSF[i + j]
        n = max(0, (time - s + f - 1) // f)
        time = s + n * f + c
    print(time)
print(0)
