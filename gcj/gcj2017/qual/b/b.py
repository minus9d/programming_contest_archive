#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def is_tidy(n):
    prev = -1
    str_n = str(n)
    for ch in str_n:
        if int(ch) < prev:
            return False
        else:
            prev = int(ch)
    return True

def simulate(n):
    for i in range(n, 0, -1):
        if is_tidy(i):
            return i

def fast(n):
    while True:
        prev = -1
        list_n = [int(x) for x in str(n)]
        if is_tidy(n):
            return n
        for i, digit in enumerate(list_n):
            if digit < prev:
                for j in range(i, len(list_n)):
                    list_n[j] = 9
                list_n[i-1] -= 1
                break
            else:
                prev = digit
        n = int(''.join([str(x) for x in list_n]))


# for i in range(1, 100000):
#     ans1 = simulate(i)
#     ans2 = fast(i)
#     if ans1 != ans2:
#         print("error! n, ans1, ans2 = ", i, ans1, ans2)
#         break
#     else:
#         print(i, ": ok")

# i = 1
# while i < int(1e18):
#     print(i, fast(i))
#     i *= 7
#     i += 52352142

def solve():
    N = int(input())
    print(fast(N))
        
def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ": ", end="")
        solve()

main()

