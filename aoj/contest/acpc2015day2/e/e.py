#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
As = []
Bs = []
movies = [[] for x in range(31)]
for n in range(N):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    As.append(a)
    Bs.append(b)
    for day in range(a, b+1):
        movies[day].append(n)

picked = [False] * N
ans = 0
for day in range(31):
    # まだ見てない映画
    unseen_movies = [m for m in movies[day] if not picked[m]]

    # 見てない映画がない
    if len(unseen_movies) == 0:
        ans += 50
    else:
        # 見てない映画のうち、終了がもっとも早いものを優先して見る
        lastday = 1000
        should_see = -1
        for m in unseen_movies:
            if Bs[m] < lastday:
                lastday = Bs[m]
                should_see = m
        picked[should_see] = True
        ans += 100
print(ans)
