#!/usr/bin/env python3
# -*- coding: utf-8 -*-

cur, goal = map(int,input().split())

ans = 1e10
if cur <= goal:
    ans = min(ans, goal - cur)
if cur <= -goal:
    ans = min(ans, 1 + (-goal - cur))
if -cur <= goal:
    ans = min(ans, 1 + (goal + cur))
if -cur <= -goal:
    ans = min(ans, 2 + (-goal + cur))
print(ans)
