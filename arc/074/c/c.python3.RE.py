# -*- coding: utf-8 -*-

def max_minus_min(areas):
    # print("areas", areas)
    return max(areas) - min(areas)

def solve2(h, w):
    area1 = h * (w // 2)
    area2 = h * w - area1
    return area1, area2

def solve(h, w):
    w_div_3 = w // 3;
    ans = 1e9
    for w2 in range(w_div_3, w_div_3 + 2):
        area1 = w2 * h
        # python3.4では'*'を使って引数を展開する文法に対応しておらずRuntime Error
        # 本番では原因を特定できなかたので、Python2に書き直した
        # 本番後、python3でも通るように修正した版を c.python3.AC.later.pyに置いた
        ans = min(ans, max_minus_min([area1, *solve2(h, w - w2)]))
        ans = min(ans, max_minus_min([area1, *solve2(w - w2, h)]))
    return ans

H, W = map(int, input().split())
print(min(solve(H,W), solve(W,H)))
