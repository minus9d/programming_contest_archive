#!/usr/bin/env python2
# -*- coding: utf-8 -*-

"""
客に提供するスライスのサイズは、必ず「どれかのパンケーキを等分したもの」になることに着目。
つまり、スライスサイズは、A[i]/1, A[i]/2, ..., A[i]/(D-1) (i = 0..N-1) のどれかになる。
あるスライスサイズについて、全探索。

Python 3だとSet2でTLE。 PyPy2だとSet2までAC
"""

from __future__ import print_function

import sys


# Python 2, 3両対応
if sys.version_info[0] == 2:
    myinput = raw_input
elif sys.version_info[0] == 3:
    myinput = input


def solve():
    N, D = map(int, myinput().split())
    As = list(map(int, myinput().split()))

    # パンケーキは小さい順に並び替えておく
    As.sort()

    ans = 10 ** 10
    for d in range(1, D + 1):
        Bs = [a * d for a in As]

        for a in As:
            # パンケーキaをd-1回カットしてd個に等分割した場合を以下で考える
            # このときの基準サイズは a / d である。
            # 有理数は扱いにくいので、すべてをd倍する。
            # つまり、パンケーキ: B
            #         基準サイズ: a

            # カット可能か調べる
            avail = 0
            for b in Bs:
                avail += b // a
            # カット不能ならcontinue
            if avail < D:
                continue

            # パンケーキBsそれぞれについて、基準サイズaでちょうど割り切れる場合、
            # 何個のパンケーキを取れるかを数える
            just = []
            for b in Bs:
                if b % a == 0:
                    just.append(b // a)

            # お得なパンケーキから順番にとっていく
            # AsやBsはあらかじめ昇順にソートしてあるので、justも昇順にソートされている
            remain_num = D  # あと何個のスライスが必要か
            cut_num = 0  # カット回数
            for j in just:
                if remain_num >= j:
                    remain_num -= j
                    cut_num += j - 1
                else:
                    break

            # 足りない分は残りのパンケーキから取る
            cut_num += remain_num

            ans = min(ans, cut_num)

    print(ans)            


def main():
    T = int(myinput())
    for testcase in range(T):
        print("Case #{}: ".format(testcase+1), end="")
        solve()


main()