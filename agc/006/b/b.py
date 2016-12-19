#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from itertools import *
def bf(n):
    variations = set()
    for comb in permutations(list(range(1,n+1))):
        top = sim(comb)
        if top not in variations:
            print(top, comb)
            variations.add(top)
        # if top != comb[ len(comb) // 2 ]:
        #     print("exception!")
        #     print("comb, result = ", comb, top)
    print(variations)

def sim(comb):
    comb = list(comb)
    while len(comb) != 1:
        n_comb = []
        for i in range(len(comb)-2):
            arr = comb[i:i+3]
            arr.sort()
            n_comb.append(arr[1])
        comb = n_comb
        # print(comb[0])
    return comb[0]

# bf(3)
# bf(5)
# bf(7)
# bf(9)
# bf(11)

def main():
    N,x = map(int,input().split())
    if N == 1:
        if x == 1:
            print('Yes')
            print(1)
        else:
            print('No')
    else:
        length = N * 2 - 1
        if 2 <= x <= length - 1:
            print('Yes')
            mid = (length + 1) // 2
            if x > mid:
                flip = True
                x = (length + 1 - x)
            else:
                flip = False

            ans = list(range(1,x-1)) + list(range(x+1,mid+1)) + list(range(x-1,x+1)) + list(range(mid+1,length+1))
            

            if flip:
                ans2 = [length + 1 - x for x in ans]
                ans = ans2
            for e in ans:
                print(e)
        else:
            print('No')

main()

