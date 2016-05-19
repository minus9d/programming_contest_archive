#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
二つの数字の差が最小となるよう、また二つ目の数字が最小となるよう'?'を埋める。
解答の方針はContest Analysisそのまま

"""

def common(S, idx, ch):
    ret = []
    for i in range(len(S)):
        if i < idx:
            ret += S[i]
        else:
            if S[i] == '?':
                ret += ch
            else:
                ret += S[i]
    return ret

def maximize(S, idx):
    """ idx以降の文字をできるだけ大きくする """
    return common(S, idx, '9')

def minimize(S, idx):
    """ idx以降の文字をできるだけ小さくする """
    return common(S, idx, '0')

def calc_diff(S1,S2):
    v1 = int("".join(S1))
    v2 = int("".join(S2))
    return abs(v1 - v2)

def dfs(S1,S2,idx):
    """
    文字列S1, S2のidx番目の文字以降を比較する。
    戻り値は、(最小差分, そのときの文字列S1, そのときの文字列S2)
    """

    # 文字列をコピーしておいた方が間違いが少ない
    S1 = S1[:]
    S2 = S2[:]

    # 末尾まで達しても差分がなかった場合、完全に同じ数字を作れる
    if idx == len(S1):
        return 0,S1,S2

    ch1 = S1[idx]
    ch2 = S2[idx]

    # (I) 文字が両方?ではない場合
    if ch1 != '?' and ch2 != '?':
        # (i) 文字が一致するなら次の文字に移る
        if ch1 == ch2:
            return dfs(S1,S2,idx+1)
        # (ii) 文字が一致しないなら、大小関係が確定
        else:
            if ch1 < ch2:
                T1 = maximize(S1, idx+1)
                T2 = minimize(S2, idx+1)
            else:
                T1 = minimize(S1, idx+1)
                T2 = maximize(S2, idx+1)
            return calc_diff(T1, T2),T1,T2

    # (II) 文字が両方?の場合
    elif ch1 == ch2 == '?':
        T1 = S1[:]
        T2 = S2[:]

        cands = []

        # (i) 両方0にして次に
        T1[idx] = T2[idx] = '0'
        cands.append(dfs(T1, T2, idx+1))

        # (ii) 0, 1として大小関係を確定させる
        T1[idx] = '0'
        T2[idx] = '1'
        U1 = maximize(T1, idx+1)
        U2 = minimize(T2, idx+1)
        cands.append((calc_diff(U1, U2), U1, U2))

        # (iii) 1, 0として大小関係を確定させる
        T1[idx] = '1'
        T2[idx] = '0'
        U1 = minimize(T1, idx+1)
        U2 = maximize(T2, idx+1)
        cands.append((calc_diff(U1, U2), U1, U2))

        return min(cands)

    # (III) 文字が片方だけ?の場合
    else:
        # ch1がdigit, ch2が'?'となるようswap
        swapped = False
        if ch1 == '?':
            ch1, ch2 = ch2, ch1
            S1, S2 = S2, S1
            swapped = True

        T1 = S1[:]
        T2 = S2[:]
        cands = []

        # (i) T1 < T2という大小関係を確定させる
        if ch1 != '9':
            T2[idx] = chr(ord(ch1) + 1)
            U1 = maximize(T1, idx+1)
            U2 = minimize(T2, idx+1)
            cands.append((calc_diff(U1, U2), U1, U2))

        # (ii) T1 > T2という大小関係を確定させる
        if ch1 != '0':
            T2[idx] = chr(ord(ch1) - 1)
            U1 = minimize(T1, idx+1)
            U2 = maximize(T2, idx+1)
            cands.append((calc_diff(U1, U2), U1, U2))

        # (iii) 両方同じ数字にして次に
        T2[idx] = ch1
        cands.append(dfs(T1, T2, idx + 1))

        # print("cands:",cands)
        mn = min(cands)
        if swapped:
            mn = (mn[0],mn[2],mn[1])
        return mn


def solve():
    S1,S2 = input().split()
    S1,S2 = [list(x) for x in (S1,S2)]

    ret = dfs(S1,S2,0)
    print("".join(ret[1]), "".join(ret[2]))


def main():
    T = int(input())
    for t in range(T):
        print ("Case #" + str(t+1) + ": ", end="")
        solve()

main()
