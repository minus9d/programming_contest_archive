#!/usr/bin/env python3

import math

def C(n1, n2):
    ans = 1
    for i in range(n1, n1-n2, -1):
        ans *= i
    for j in range(1, n2+1):
        ans //= j
    return ans

N, A, B = map(int, input().split())
Vs = list(map(int, input().split()))
Vs.sort()
Vs.reverse()

avg = 0.0
way = 0
for num_of_choice in range(A, B + 1):
    choiced = []
    for n in range(num_of_choice):
        choiced.append(Vs[n])
    if choiced[0] == choiced[-1]:
        avg = choiced[0]
        way += C(Vs.count(choiced[0]), num_of_choice)
    else:
        if way != 0:
            break
        border = choiced[-1]
        n1 = Vs.count(border)
        n2 = choiced.count(border)
        avg = sum(choiced) / num_of_choice
        way = C(n1, n2)
        break

print("{:.12f}".format(avg))
print(way)
