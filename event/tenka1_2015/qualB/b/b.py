#!/usr/bin/env python3
# -*- coding: utf-8 -*-
 
s = input()
 
def split_into_expr(s):
    cnt = 0
    ret = []
    tmp = ""
    for ch in s[1:-1]:
        if ch == "{":
            cnt += 1
        elif ch == "}":
            cnt -= 1
        elif ch == ",":
            if cnt == 0:
                ret.append(tmp)
                tmp = ""
                continue
        tmp += ch
    if tmp != "":
        ret.append(tmp)
    return ret
 
# print(split_into_expr("{2,3,4,5}"))
# print(split_into_expr("{2,{3:{4:5}},{4:2},5}"))
 
def has_colon(s):
    cnt = 0
    for ch in s:
        if ch == "{":
            cnt += 1
        elif ch == "}":
            cnt -= 1
        elif ch == ":":
            if cnt == 0:
                return True
    return False
 
 
# print(has_colon("{{2:3},7,{2:{4:5}}")) # False
# print(has_colon("{{3:4,2:5}:4")) # True
 
if s == "{}":
    print("dict")
else:
    exprs = split_into_expr(s)
    if has_colon(exprs[0]):
        print("dict")
    else:
        print("set")
 
# t = type(eval(s))
# if "dict" in str(t):
#     print("dict")
# else:
#     print("set")
