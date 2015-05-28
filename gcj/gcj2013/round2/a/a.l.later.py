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

# 座標圧縮
def compress(oep):
    # 出現する駅とその前後を収集
    coords = set()
    for (o,e,p) in oep:
        for station in [o,e]:
            for offset in [0,-1,1]:
                val = station + offset
                if val >= 0:
                    coords.add(val)
                    
    coords = sorted(list(coords))
    mx = len(coords)

    # 変換テーブル作成
    new_to_old = {}
    old_to_new = {}
    for i in range(len(coords)):
        new_to_old[i] = coords[i]
        old_to_new[coords[i]] = i

    # oepを新座標に変換
    oep_compressed = []
    for (o,e,p) in oep:
        oep_compressed.append( (old_to_new[o], old_to_new[e], p) )

    # print("new_to_old: ", new_to_old)
    # print("old_to_new: ", old_to_new)
    # print("oep:")
    # print(oep)
    # print("oep_compressed:")
    # print(oep_compressed)

    return oep_compressed, new_to_old, mx

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

    oep_uncompressed = []
    for m in range(M):
        o,e,p = map(int, input().split())
        o -= 1
        e -= 1
        oep_uncompressed.append((o,e,p))

    # 座標圧縮する
    oep, convert_table, mx = compress(oep_uncompressed)

    # 駅と駅の間を取り出す
    stations = [0] * mx
    for o,e,p in oep:
        for i in range(o, e):
            stations[i] += p

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

    # 元の座標に戻す
    new_oep_uncompressed = []
    for (o,e,p) in new_oep:
        new_oep_uncompressed.append((convert_table[o],convert_table[e],p))

    before = calc_whole_score(oep_uncompressed, N)
    after = calc_whole_score(new_oep_uncompressed, N)
    return (before - after) % 1000002013


def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ":", solve())

main()

