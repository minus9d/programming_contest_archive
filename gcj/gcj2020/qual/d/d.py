#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
最初の10回のクエリを使って、
入力文字列の最初の5個、最後の5個の中から
00xxx...xxx10
のようなパターンを見つける

次のクエリ10回のうち、最初の2回で、
00
だった場所の値を調べる

00: complementなし reverseなし
11: complementあり reverseなし
10: complementなし reverseあり
01: complementあり reverseあり
"""



# インタラクティブ問題のメモ
#   標準出力にはprint2(), 標準エラー出力にはprinte()を使う
#
#   デバッグ用ツールを動かすには
#     python interactive_runner.py python testing_tool.py 1 -- ./d.later.py
#   などとする。1の部分には0, 1をいれる
#     Judge return code: 0
#     Solution return code: 0
#   となればOK

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import random
import re
import string
import sys


def print2(*args, **kwargs):
    print(*args, **kwargs)
    sys.stdout.flush()


def printe(*args, **kwargs):
    print(*args, **kwargs, file=sys.stderr)
    sys.stderr.flush()


def solve_10():
    ans = ''

    for i in range(10):
        print2(i + 1)
        res = input()
        ans += res

    printe("ans = ", ans)
    print2(ans)
    result = input()
    assert result == 'Y'
    

def query_to_know_bits(B):
    # bitsの状態を判別できる2bitの位置を特定
    # クエリ10回投げるのを2回以内でできることを想定

    head = ''
    tail = ''

    while len(head) < B // 2:

        # 初回はhead, tailを5回ずつ
        if not head:
            for j in range(5):
                print2(j + 1)
                head += input()
                print2(B - j)
                tail += input()

            printe("head, tail = ", head, tail)

        else:
            # ここに来たということは、
            #  head = 00111  tail = 00111 などのパターンと
            #  head = 00111  tail = 11000 などのパターンのどちらか

            # 直前のを調べる
            idx = len(head) - 1
            print2(idx + 1)
            val1 = input()
            print2(B - idx)
            val2 = input()
            printe("val1, val2 = ", val1, val2)
            if head == tail:
                if head[-1] != val1:
                    head = tail = compliment_bits(head)
            elif head == compliment_bits(tail):
                if head[-1] != val1:
                    head, tail = tail, head
            else:
                # ありえない
                raise ExceptionError

            j = 0
            idx += 1
            while j < 4 and len(head) < B // 2:
                print2(idx + 1)
                head += input()
                print2(B - idx)
                tail += input()
                idx += 1
                j += 1

            printe("head, tail = ", head, tail)

            # ここでいっぱいになる場合終了
            if idx == B // 2:
                ans = head + tail[::-1]
                print2(ans)
                res = input()
                return None

        # 00 + 01のようなビットを作れたか？
        same_bits = []
        different_bits = []

        size = len(head)
        for i in range(size):
            if head[i] == tail[i]:
                same_bits.append(i)
            else:
                different_bits.append(i)

        printe("same_bits = ", same_bits)
        printe("diff_bits = ", different_bits)
                
        if same_bits and different_bits:
            printe("ok done!")
            bits_to_be_examined = [same_bits[0], different_bits[0]]
            head_pattern = (head[same_bits[0]] + head[different_bits[0]])
            tail_pattern = (tail[same_bits[0]] + tail[different_bits[0]])
                            
            printe("head:", head)
            printe("tail:", tail)
            printe("examined bits:", bits_to_be_examined)
            printe("head p:", head_pattern)
            printe("tail p:", tail_pattern)
            return bits_to_be_examined, head_pattern, tail_pattern, head, tail
        else:
            printe("fail... continued.")


def compliment_bits(s):
    ret = ''
    for ch in s:
        if ch == '0': ret += '1'
        else: ret += '0'
    return ret


def check_compliment_and_reverse(head_pattern, tail_pattern, pattern):
    if pattern == head_pattern:
        return False, False
    elif pattern == tail_pattern:
        return False, True
    elif pattern == compliment_bits(head_pattern):
        return True, False
    else:
        return True, True


def solve_more_than_10(B):

    res = query_to_know_bits(B)
    if res is None:
        return

    bits_to_be_examined, head_pattern, tail_pattern, head, tail \
        = res

    printe("bits_to_be_examined, head_pattern, tail_pattern, head, tail = ",
           bits_to_be_examined, head_pattern, tail_pattern, head, tail)

    # これまでにわかった分を代入
    ans = [None] * B
    for j, h in enumerate(head):
        ans[j] = h
    for j, t in enumerate(tail):
        ans[-(j + 1)] = t

    # まだ調べられていないところから再開
    i = len(head)

    printe("ans = ", ans)

    # 'head'に近い方のうち調べていない方から順に調べる
    while i < B:

        # もうすべてのビットを調べ終えた
        if ans[i] is not None:
            printe("ans[{}] is already done. break".format(i))
            break

        # 特定の2bitを見る
        pattern = ''
        for bit in bits_to_be_examined:
            print2(bit + 1)
            pattern += input()
        printe("got pattern {}".format(pattern))

        # 2bitから、文字列の状態を推定
        complement_flag, reverse_flag \
            = check_compliment_and_reverse(head_pattern, tail_pattern, pattern)

        # 'head'に近い方のうち調べていない方から順に8bitを調べる
        for _ in range(8):

            if reverse_flag:
                print2(B - i)
            else:
                print2(i + 1)
    
            res = input()

            if complement_flag: res = compliment_bits(res)

            ans[i] = res
            i += 1

            if i == B:
                break

    printe("ans = ", ans)
    joined = ''.join(ans)

    # 現在の状態に応じて変更
    if reverse_flag: joined = joined[::-1]
    if complement_flag: joined = compliment_bits(joined)

    printe("query(joined): ", joined)
    print2(joined)

    result = input()
    printe("result = ", result)


def solve(B):

    if B == 10:
        solve_10()
    else:
        solve_more_than_10(B)


T, B = map(int, input().split())
for testcase in range(T):
    solve(B)
sys.exit(0)
