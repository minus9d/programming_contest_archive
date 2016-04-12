#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys

def solve(N,J):
    numstr = "1" + "0" * (N-1)
    num = int(numstr, 2)

    ans = []
    while True:
        num += 1

        binstr = bin(num)[2:]

        # if binstr.count("1") % 2:
        #     continue
        if binstr[-1] == '0':
            continue

        ok = True
        divisors = []
        for base in range(2,11):
            val = int(binstr, base)
            cands = [2,3,5,7,11]
            for c in cands:
                if val % c == 0:
                    divisors.append(c)
                    break
            else:
                ok = False
                break

        if ok:
            ans.append([binstr] + divisors)
            if len(ans) == J:
                break

            # validation
            for i, base in enumerate(range(2,11)):
                val = int(binstr, base)
                # print("for base {}, {} % {} = {}.".format(base, val, divisors[i], val % divisors[i])
                if val % divisors[i] != 0:
                    print("error!!!")
                    sys.exit(0)
            
            


    for a in ans:
        print (' '.join([str(x) for x in a]))

    # for j in jamcoins:
    #     print (' '.join([str(bin(j))[2:], '3', '2', '3', '2', '3', '2', '3', '2', '3']))

T=int(input())
for testcase in range(T):
    N,J = [int(x) for x in input().split()]
    print("Case #{}:".format(testcase+1))
    solve(N,J)
