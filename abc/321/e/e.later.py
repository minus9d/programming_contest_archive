#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
https://www.youtube.com/watch?v=DqWQ4_io3vo
の通りに実装
"""

def solve(N, X, K):

    # # 頂点数Nが最大のときでも深さは60程度
    # if K > 120:
    #     return 0


    def count_down(v, d):
        """頂点vから下にd進んだところの頂点の数を返す
        """
        l = v << d
        r = min(N, (v << d) + (1 << d) - 1)
        return max(0, r - l + 1)

    ans = 0

    # x: 今注目している点
    # px: 前にいた点
    x, px, k = X, -1, K

    while x > 0 and k >= 0:

        if x == X:
            # 最初は、今いる場所から下にk進んだところの頂点数を数える
            ans += count_down(x, k)
        else:
            if k == 0:
                # 今いるところの分を数える
                ans += 1
            else:
                # 前にいた点(px)の兄弟を取得してyに代入
                if px == 2 * x + 1:
                    y = 2 * x
                else:
                    y = 2 * x + 1
                # 実はこの4行は以下のようにも書ける
                # y = px ^ 1
                # 兄弟から下にk-1進んだところの頂点数を数える
                ans += count_down(y, k - 1)

        # ひとつ上の階層に進む
        x, px = x // 2, x
        k -= 1

    return ans


T = int(input())
for t in range(T):
    N, X, K = map(int, input().split())
    print(solve(N, X, K))
