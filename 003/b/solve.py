#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re

def isOK(ch):
    pattern = re.compile(r'[atcoder]')
    if pattern.match(ch):
        return True
    else:
        return False
        
s1=input()
s2=input()
ok=True
for (i,ch) in enumerate(s1):
    if s1[i] == s2[i]:
        continue
    elif s1[i] == '@':
        if not isOK(s2[i]):
            ok = False
            break
    elif s2[i] == '@':
        if not isOK(s1[i]):
            ok = False
            break
    elif s1[i] != s2[i]:
        ok = False
        break
if ok:
    print("You can win");
else:
    print("You will lose");

