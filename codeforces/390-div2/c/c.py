#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def extract(text, users):
    text = text.replace(".", "")
    text = text.replace(",", "")
    text = text.replace("!", "")
    text = text.replace("?", "")
    words = set(text.split())
    return users & words

def solve():
    N = int(input())
    users = set(input().split())
    M = int(input())

    taboo = [set() for m in range(M)]
    info = []
    for m in range(M):
        speaker, text = input().split(':')
        included_users = extract(text, users)
        info.append((speaker, included_users))

    for m in range(M):
        taboo[m] |= info[m][1]
        try:
            taboo[m] |= info[m-1][0]
        except:
            pass
        try:
            taboo[m] |= info[m+1][0]
        except:
            pass

    print("taboo:",taboo)

T = int(input())
for t in range(T):
    solve()
