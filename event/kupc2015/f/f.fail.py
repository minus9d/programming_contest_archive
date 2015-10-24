#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# http://stackoverflow.com/questions/16176742/python-3-replacement-for-deprecated-compiler-ast-flatten-function
def flatten(x):
    result = []
    for el in x:
        if hasattr(el, "__iter__") and not isinstance(el, str):
            result.extend(flatten(el))
        else:
            result.append(el)
    return result

# validation
def Prog(S, stack):
    buf = []
    for ch in S:
        if ch.isdigit():
            buf.append(ch)
        else:
            # Program S
            if stack:
                r = int(buf.pop())
                l = int(buf.pop())
            # Program Q
            else:
                r = int(buf.pop(0))
                l = int(buf.pop(0))

            tmp = 0
            if ch == '+':
                tmp = l + r
            elif ch == '-':
                tmp = l - r
            elif ch == '*':
                tmp = l * r
            buf.append(tmp)
    return(buf[0])

def calc(S):
    # corner case
    if len(S) == 1:
        return S

    buf = []

    nums = []
    ops = []

    ans = []

    for ch in S:
        if ch.isdigit():
            buf.append(ch)
        else:
            r = buf.pop()
            l = buf.pop()
            op = ch
            print("l,r are popped.", l, r)
            print("op: ", op)
            print("")


            if len(ops) == 0:
                ans.append([l,r])
            else:
                ans.append(l)
                ans.append(ops)
                ops = []

            buf.append("dummy")

    return "".join(flatten(ans))
    # return "".join(flatten(buf))



S = input()
ans = calc(S)

print("s: ", S)
print("prog s: ", Prog(S, True))
print("ans: " , ans) 
print("prog q: ", Prog(ans, False))
print(ans)

# bf
import itertools
goal = Prog(S,True)
seen = {}
for i in itertools.permutations(S):
    cand = "".join(i)
    if cand in seen:
        continue
    try:
        t = Prog(cand, False)
    except:
        continue
    if t == goal:
        print("cand ", cand, "is good")
    seen[cand] = 1
