#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itertools
import sys

def solve(K,C,S):

    minimum = (K + C - 1) // C
    if S < minimum:
        print ("IMPOSSIBLE")
        return

    ans = []
    nxt = 0
    for m in range(minimum):
        idx = 0
        for c in range(C-1,-1,-1):
            idx += (K**c) * nxt
            # print("{}**{}*{} is added".format(K,c,nxt))
            nxt += 1
            if nxt == K:
                nxt -= 1
        ans.append(idx)
    print(" ".join(str(x+1) for x in ans))

    # validate

    # LLL, GLL, LGL, LLGのみ調べればOK
    print("validation")
    ret = [False] * len(ans)
    inits = ["".join(x) for x in itertools.product("GL", repeat=K)]
    inits = [x for x in inits if x.count("G") == 1]
    finals = []
    for p in inits:
        # print("first:",p)

        first = p[:]
        for _ in range(C-1):
            tmp = ""
            for ch in p:
                if ch == 'G':
                    tmp += 'G'*K
                else:
                    tmp += first
            p = tmp
            # print(" after iter:", p)
        #print(first, " ", p)
        print(first, ": ", " ".join( [p[i:i+K] for i in range(0, len(p), K)] ))
        finals.append(p)

    print("finals:",finals)
    print("ans:",ans)

    for f in finals:
        for a_idx, a in enumerate(ans):
            if f[a] == 'G':
                ret[a_idx] = True
    if all(ret):
        print("ok!")
    else:
        print("fail!!!")

    return


    # experiments

    inits = ["".join(x) for x in itertools.product("GL", repeat=K)]

    # LLL, GLL, LGL, LLGのみ調べればOK
    inits = [x for x in inits if x.count("G") == 1]
    
    finals = []
    for p in inits:
        # print("first:",p)

        first = p[:]
        for _ in range(C-1):
            tmp = ""
            for ch in p:
                if ch == 'G':
                    tmp += 'G'*K
                else:
                    tmp += first
            p = tmp
            # print(" after iter:", p)
        #print(first, " ", p)
        print(first, ": ", " ".join( [p[i:i+K] for i in range(0, len(p), K)] ))
        finals.append(p)

    # 縦読みしたときのGの数を数える
    gnums = []
    size = len(finals[0])
    for i in range(size):
        s = sum([1 for f in finals if f[i] == 'G'])
        gnums.append(s)


    print("gnums:", ''.join([str(x) for x in gnums]))
    print("max of g:", max(gnums))
    print("idx of max g:", [i+1 for i in range(size) if gnums[i] == max(gnums)])



    print("------")

# k = int(sys.argv[1])
# C = k+5
# for c in range(1, C):
#     print("c:",c)
#     solve(k,c,100)
# sys.exit(0)

T=int(input())
for testcase in range(T):
    K,C,S = [int(x) for x in input().split()]
    print("Case #{}: ".format(testcase+1), end='')
    solve(K,C,S)
