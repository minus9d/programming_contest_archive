#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys

def calc_score(data, N):
    o = data[0]
    e = data[1]
    p = data[2]
    k = e - o + 1  # 通過駅数  同じ駅で降りたら1, 1駅移動したら2
    return ((k - 1) * (N - 1) - (k - 1) * k // 2) * p

def calc_whole_score(oep, N):
    score = 0
    for tpl in oep:
        score += calc_score(tpl, N)
    return score

def pick_longest(stations, i):
    if stations[i] == 0:
        return None
    
    mn = stations[i]    
    end = i
    
    for j in range(i,len(stations)):
        if stations[j] == 0:
            break
        else:
            mn = min(mn, stations[j])
            end = j
    
    # iからendまでmnずつ引く
    for k in range(i, end+1):
        stations[k] -= mn
    
    return (i,end+1,mn)


# 入力の経路が以下の場合を考える
#   (0)-(1)-(2)              * 2
#           (2)-(3)-(4)-(5)  * 1
# 駅と駅の間の通過数を取り出して足し合わせる
#      2   2
#              1   1   1
#   ↓
#      2   2   1   1   1
# 22111から長い数字をgreedyにとっていく
#   11111
#   11
# (2)で乗って(2)で降りる分が表せていないが、運賃ゼロなので問題ない
def solve():
    N,M = map(int, input().split())

    stations = [0] * (N-1)

    oep = []
    for m in range(M):
        o,e,p = map(int, input().split())
        o -= 1
        e -= 1
        for i in range(o, e):
            stations[i] += p
        oep.append((o,e,p))

    # print("oep")
    # print(oep)
    # print("stations")
    # print(stations)

    # greedyに長い数字をとっていく
    new_oep = []
    for i in range(len(stations)):
        while stations[i] != 0:
            picked = pick_longest(stations, i)
            new_oep.append(picked)
            # print("stations in change")
            # print(stations)

    # print("new oep")
    # print(new_oep)

    before = calc_whole_score(oep, N)
    after = calc_whole_score(new_oep, N)
    return before - after


def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ":", solve())

main()

