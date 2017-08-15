#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import bisect
import sys

N, K = map(int,input().split())
As = [int(x)-1 for x in input().split()]
As_set = set(As)

inc = []
exc = []
for n in range(N):
    s = input()
    if n in As_set:
        inc.append(s)
    else:
        exc.append(s)

inc.sort()
exc.sort()

def ok(ini_str):
    loc = bisect.bisect_left(exc, ini_str)
    if loc == len(exc):
        return True
    else:
        return not exc[loc].startswith(ini_str)

# corner case
if N == K:
    print()
    sys.exit(0)

for n in range(1000000):
    if len(inc[0][:n]) != n or inc[0][:n] != inc[-1][:n]:
        print(-1)
        sys.exit(0)
    else:
        if ok(inc[0][:n]):
            print(inc[0][:n])
            sys.exit(0)
