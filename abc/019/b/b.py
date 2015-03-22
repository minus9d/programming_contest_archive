#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def cnt_seq(ch, S):
    cnt = 0
    for i in range(len(S)):
        if S[i] == ch:
            cnt += 1
        else:
            break
    return cnt

S = input()
ret = ""
while len(S) > 0:
    seq = cnt_seq(S[0], S)
    ret += S[0] + str(seq)
    S = S[seq:]
print(ret)
    
