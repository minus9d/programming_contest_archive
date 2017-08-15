#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def flip(S, idx, K):
    for j in range(idx, idx + K):
        S[j] = '-' if S[j] == '+' else '+'
    return S

def solve():
    S, K = input().split()
    S = list(S)
    K = int(K)

    ans = 0
    for i in range(len(S) - K + 1):
        if S[i] == '-':
            ans += 1
            S = flip(S, i, K)
    if '-' in S:
        print("IMPOSSIBLE")
    else:
        print(ans)
        
def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ": ", end="")
        solve()

main()

