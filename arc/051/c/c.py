#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# コンテスト終了後にコード整理

MOD = 1000000007

N,A,B = [int(x) for x in input().split()]
arr = [int(x) for x in input().split()]
arr.sort()

turn = 0
prev = None

cache = {}

while True:
    # process
    new_arr = [arr[0] * A] + arr[1:]
    new_arr.sort()
    arr = new_arr

    turn += 1
    if turn == B:
        print("\n".join( [str(x%MOD) for x in arr] ))
        break

    # 十分ループした後は定常状態に入っているはず
    # 十分ループした後、N回ループすると、順番は同じですべての要素がA倍される
    enough = 1000
    if enough <= turn < enough + N:
        cache[turn] = arr

    elif turn >= enough + N:
        turn = B

        diff = turn - enough
        v1 = diff % N
        v2 = diff // N

        tmp = [(x * pow(A,v2,MOD)) % MOD for x in cache[enough + v1]]

        print("\n".join(str(x) for x in tmp))
        break
