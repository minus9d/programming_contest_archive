#!/usr/bin/env python3
# -*- coding: utf-8 -*-


def solve():
    S = input()
    ret = ""
    for ch in S:
        if ret == "":
            ret += ch
        else:
            if ret[0] <= ch:
                ret = ch + ret
            else:
                ret += ch
    return ret

def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ":", solve())

main()

