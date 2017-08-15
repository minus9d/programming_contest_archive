#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Vの隣に来れるのはYのみ。
(i) VとYしかない場合
　　VとYが同数である場合のみ円環が作れる
　（本番ではこのケースに気づかなかった）
(ii) VとY 以外にも要素がある場合
   Yの数はVの数を1以上上回っていなければならない。
   この条件を満たせば, YVYVY と、Vを隠蔽してあたかもY1つのように扱える。
   あとはSmallと同じ
"""


def validate(N, R, O, Y, G, B, V, ans):
    if len(ans) != N:
        print("error! len differs")
    elif ans.count('R') != R:
        print("error! r count")
    elif ans.count('G') != G:
        print("error! g count")
    elif ans.count('B') != B:
        print("error! b count")
    elif ans.count('O') != O:
        print("error! o count")
    elif ans.count('Y') != Y:
        print("error! y count")
    elif ans.count('V') != V:
        print("error! v count")
    else:
        ans += ans[0]
        errs = ['RR', 'GG', 'BB', 'RO', 'YO', 'YG', 'BG', 'RV', 'BV']
        for err in errs:
            if err in ans or err[::-1] in ans:
                print("error! {} exists".format(err))
                return

    print("ok")

def is_y_and_v_ok(Y, V, N):
    return Y + V == N and Y == V

def y_and_v(y_ch, v_ch, Y, V):
    ans = []
    for i in range(Y):
        ans += [y_ch, v_ch]
    return ''.join(ans)

def create(y_ch, v_ch, Y, V):
    ret = []
    t = ''
    for v in range(V):
        t += y_ch + v_ch
    if t != '':
        ret.append(t + y_ch)
        for y in range(Y - V - 1):
            ret.append(y_ch)
    else:
        for y in range(Y):
            ret.append(y_ch)

    return ret

def y_and_v_is_fail(Y, V):
    if V > 0 and Y < V + 1:
        return True
    return False

def solve_small(N, R, O, Y, G, B, V):
    nums =  [R, O, Y, G, B, V]
    names = ['R', 'O', 'Y', 'G', 'B', 'V']
    mx = max(nums)
    if mx <= N // 2:
        pairs = list(zip(nums, names))
        ans = ''
        prev = 'z'
        for n in range(N):
            pairs.sort()
            pairs.reverse()
            for m in range(N):
                if pairs[m][1] != prev:
                    ans += pairs[m][1]
                    pairs[m] = (pairs[m][0]-1, pairs[m][1])
                    prev = pairs[m][1]
                    if n == 0:
                        pairs[m] = (pairs[m][0] + 0.1, pairs[m][1])
                    break
        # validate(N, R, O, Y, G, B, V, ans)
        print(ans)
    else:
        print("IMPOSSIBLE")


def solve(N, R, O, Y, G, B, V):
    nums =  [R, O, Y, G, B, V]
    names = ['R', 'O', 'Y', 'G', 'B', 'V']
    mx = max(nums)

    # corner case:
    #   Y V Y V
    if is_y_and_v_ok(Y, V, N):
        print(y_and_v('Y', 'V', Y, V))
    elif is_y_and_v_ok(R, G, N):
        print(y_and_v('R', 'G', R, G))
    elif is_y_and_v_ok(B, O, N):
        print(y_and_v('B', 'O', B, O))

    elif y_and_v_is_fail(Y, V):
        print("IMPOSSIBLE")
    elif y_and_v_is_fail(R, G):
        print("IMPOSSIBLE")
    elif y_and_v_is_fail(B, O):
        print("IMPOSSIBLE")
    else:
        ys = create('Y', 'V', Y, V)
        rs = create('R', 'G', R, G)
        bs = create('B', 'O', B, O)

        # print("")
        # print("ys:", ys)
        # print("rs:", rs)
        # print("bs:", bs)

        nums2 = [len(ys), len(rs), len(bs)]
        names2 = ['Y', 'R', 'B']
        N2 = sum(nums2)

        mx = max(nums2)
        if mx > N2 // 2:
            print("IMPOSSIBLE")
        else:
            pairs = list(zip(nums2, names2))
            ans = ''
            prev = 'z'
            for n in range(N2):
                pairs.sort()
                pairs.reverse()
                for m in range(N2):
                    if pairs[m][1] != prev:
                        sign = pairs[m][1]
                        if sign == 'Y':
                            ans += ys[-1]
                            ys = ys[:-1]
                        elif sign == 'R':
                            ans += rs[-1]
                            rs = rs[:-1]
                        elif sign == 'B':
                            ans += bs[-1]
                            bs = bs[:-1]
                        # print("now::::")
                        # print("ys:", ys)
                        # print("rs:", rs)
                        # print("bs:", bs)

                        pairs[m] = (pairs[m][0]-1, pairs[m][1])
                        prev = pairs[m][1]
                        if n == 0:
                            pairs[m] = (pairs[m][0] + 0.1, pairs[m][1])
                        break
            # validate(N, R, O, Y, G, B, V, ans)
            print(ans)

# # debug
# aaa = 10
# for r in range(aaa):
#     for o in range(aaa):
#         for y in range(aaa):
#             for g in range(aaa):
#                 for b in range(aaa):
#                     for v in range(aaa):
#                         n = r + o + y + g + b + v
#                         if n == 0: continue
#                         ans = solve(n, r, o, y, g, b, v)



T = int(input())
for testcase in range(T):
    N, R, O, Y, G, B, V = map(int, input().split())
    print("Case #{}: ".format(testcase+1), end="")
    solve(N, R, O, Y, G, B, V)
