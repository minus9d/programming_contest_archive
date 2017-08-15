#!/usr/bin/env python3

# 解説PDFそのまま https://atcoder.jp/img/agc012/editorial.pdf

# Nが7以上15未満の場合は、まず以下のような数列を作成。
#  [1, 2, 3, 1, 2, 3]
# これからとれる良い文字列の数は、7個(11, 1212, 1313, 123123, 22, 2323, 33)。
# 次に 4を挿入する位置で、よい文字列の増加数を調節できる。
#  [1, 2, 4, 3, 1, 2, 3, 4] なら 4増加。
#  [1, 4, 2, 3, 1, 2, 3, 4] なら 2増加。
#  [4, 1, 2, 3, 1, 2, 3, 4] なら 1増加。

def construct(N):
    # [1, 2, 3]に相当するリストを作成
    for n in range(40, -1, -1):
        if N >= (1 << n) - 1:
            break
    p = []
    for i in range(1, n+1):
        p.append(i)

    # 4, 5, 6 のうち必要なものを後ろから入れていく
    N -= (1 << n) - 1
    for i in range(n-1, -1, -1):
        if N < (1 << i):
            continue
        n += 1
        p = p[:i] + [n] + p[i:]
        N -= 1 << i
    return p

N = int(input())
part = construct(N)
ans = part + [x + 1 for x in range(len(part))]
print(len(ans))
print(*ans, end=' ')
print()
