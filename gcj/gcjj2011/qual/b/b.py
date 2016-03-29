#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import namedtuple

T = int(input())
for testcase in range(T):
    N, K = (int(x) for x in input().split())
    Cs = [0] * N
    Ts = [0] * N
    Ss = [0] * N
    for n in range(N):
        Cs[n],Ts[n],Ss[n] = [int(x) for x in input().split()]

    # print("Cs:",Cs)
    # print("Ts:",Ts)
    # print("Ss:",Ss)

    expiry_days = sorted(list(set([0] + Ts)))
    choices = set()
    output = 0

    # GCJJの解説だとうまく動かなかったので修正
    day = expiry_days[-1]
    expiry_days.pop()

    # print("expiry_days:",expiry_days)

    while day >= 1:
        # print("------")
        # print("day:",day)

        choices.update(i for i in range(N) if Ts[i] == day)
        # print("choices:",choices)
        if len(choices) > 0:
            j = max(choices, key=lambda x: Ss[x])
            # print("chose:",j)

            if (day - Cs[j]) >= expiry_days[-1]:
                # print("all use")
                output += Ss[j] * Cs[j]
                day -= Cs[j]
                choices.remove(j)
            else:
                # print("part use")
                # print("Ss[j], day, ex[-1]=", Ss[j], day, expiry_days[-1])
                output += Ss[j] * (day - expiry_days[-1])
                Cs[j] -= (day - expiry_days[-1])
                day = expiry_days[-1]
                expiry_days = expiry_days[:-1]
        else:
            day = expiry_days[-1]
            expiry_days.pop()
        # print("output:",output)

    print("Case #{}: {}".format(testcase+1, output))

        
    
