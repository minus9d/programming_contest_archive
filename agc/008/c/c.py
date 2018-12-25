#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def greedy(J,L,I):
    ans = 0
    ans += (J // 2) * 2
    ans += (L // 2) * 2
    J -= (J // 2) * 2
    L -= (L // 2) * 2
    if J * L * I > 0:
        ans += 3
        I -= 1
    ans += (I // 2) * 2
    return ans

def solve(I,O,T,J,L,S,Z):
    ans = O
    tmp1 = greedy(J,L,I)
    if J * L * I > 0:
        tmp1 = max(tmp1, 3 + greedy(J-1,L-1,I-1))
    ans += tmp1
    return ans
    
I,O,T,J,L,S,Z = map(int,input().split())
print(solve(I,O,T,J,L,S,Z))

# assert(solve(0,0,0,0,0,0,0) == 0)
# assert(solve(2,0,0,0,0,0,0) == 2)
# assert(solve(3,0,0,0,0,0,0) == 2)
# assert(solve(4,0,0,1,1,0,0) == 5)
# assert(solve(4,0,0,2,1,0,0) == 6)
