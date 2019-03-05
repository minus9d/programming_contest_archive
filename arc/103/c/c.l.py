# 場合分けで混乱して大苦戦。3WAののち解説や他人の回答を見てAC
#
# 最初、最頻出文字が複数ある場合を考慮した場合分けを
# しようとしていたが、複雑になりすぎた。
# この実装だと、最頻出文字が複数ある場合も自然に(ii)でカバーできる

from collections import *
N = int(input())
As = list(map(int, input().split()))

def solve(arr1, arr2):
    cnt1 = Counter(arr1)
    cnt2 = Counter(arr2)

    most1 = cnt1.most_common()
    most2 = cnt2.most_common()

    # 1文字しかないときの処理を簡単にするためにダミーのエントリを追加
    most1.append(('_', 0))
    most2.append(('_', 0))

    # (i) 最頻出文字が異なる → 単に最頻出文字を採用すればよい
    if most1[0][0] != most2[0][0]:
        return len(arr1) * 2 - most1[0][1] - most2[0][1]
    # (ii) 最頻出文字が同じ → 2通り試して良い方を採用
    else:
        ans1 = len(arr1) * 2 - most1[0][1] - most2[1][1]
        ans2 = len(arr1) * 2 - most1[1][1] - most2[0][1]
        return min(ans1, ans2)

arr1 = As[0::2]
arr2 = As[1::2]
print(solve(arr1, arr2))
