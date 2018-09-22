#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# [問題]
#   Nが与えられる。
#   以下の条件を満たす、N個の山を構成せよ。
#     Nimゲームで先攻が勝つような先攻のmove (winning move) 数を最大化する
#     各山の石の個数は1 ~ 737373737個
#   Nは1~37。
#
# [解法]
#   まずNimの勝利条件を蟻本で確認。
#   これによると、N個の山の石の数でxorをとった結果が0なら負け、非0なら勝ちの状態である。
#
#   まずNが奇数の場合を考える。
#   例えば山が5個あるとする。
#   山を順にa, b, c, d, e,
#   各山の石の数をn(a), n(b), ...とする。
#
#   １つ目の山から任意の個数の石を取り除いたあと、
#   勝ちの状態を作れるか、言い換えると、残りの山のXORをちょうど0にできるか、を考えてみる。
#
#   石の個数をa, b, c, d, eだとすると、
#   山aから石を取り除いた後の値が、n(b) ^ n(c) ^ n(d) ^ n(e)に等しくなることが、
#   この山から石を取る場合の唯一の勝利条件である。
#
#   必要な条件は、n(a) > n(b) ^ n(c) ^ n(d) ^ n(e)。
#
#   ここで、n(a) = 0b100001
#          n(b) = 0b100010
#          n(c) = 0b100011
#          n(d) = 0b100100
#          n(e) = 0b100101
#   としてみると、n(b) ^ n(c) ^ n(d) ^ n(e)の結果、最上位ビットは0になる。
#   よって n(a) > (n(b) ^ n(c) ^ n(d) ^ n(e)) とできるので、
#   n(a)から石をとることで相手を負けにできる。
#   Nが奇数のときはこの構成法でN種類のwinning moveができる。
#
#   Nが偶数のときは、実はN-1種類のwinning moveが常に最大値となる。
#   N = 4の場合を考えると、
#          n(a) = 0b100001
#          n(b) = 0b100010
#          n(c) = 0b100011
#          n(d) = 0b000001
#   と、最後の山を1にすることで、N-1種類のwinning moveができる。
#
#   では、N種類のwinning moveは可能なのか。
#   本番中では、実験的に不可能でありそうなことを確かめたが、
#   証明はできなかった。https://www.topcoder.com/blog/single-round-match-737-editorials/ 
#   を読んで、証明を理解できた。
#   
#   証明:
#   今、Nが偶数で、winning positionにいるとする。(つまり先手が石を取る直前である）
#   すべての石のxorは非ゼロなので、
#   すべての石のxorをとった値のうち、もっとも左側の1が立つビットの位置をxとする。
#   山の数は偶数だが、x番目のビットが立っている山の数は奇数である。
#   ということは、少なくとも1つの山(Pとおく)は、そのx番目のビットが立っていない。
#   山Pについては、どう石をとっても、先手は勝てない。
#   よってNが偶数の場合は、最大でもN-1種類のwinning moveしかできない。
#
# [本番]
#   ブサイクだが上記とほぼ同じ実装ができた。
#   生成された配列が条件を満たすかチェックする関数を作っていたので2個撃墜できた


import array
from bisect import *
from collections import *
import fractions
import heapq
from itertools import *
import math
import re
import string

class AliceAndBobEasy:
    def make(self, N):
        if N == 1:
            return (737,)
        elif N == 2:
            return (737, 373)
        elif N % 2 == 1:
            ret = []
            ret.append(1 << 28)
            ret.append((1 << 28) + (1 << 27))
            ret.append((1 << 28) + (1 << 26))
            for i in range(N - 3):
                ret.append((1 << 28) + i + 1)
            return tuple(ret)
        else:
            ret = []
            ret.append(1)
            ret2 = list(self.make(N - 1))
            ret += ret2
            return tuple(ret)
            

# CUT begin
# TEST CODE FOR PYTHON {{{
import sys, time, math

def tc_equal(expected, received):
    try:
        _t = type(expected)
        received = _t(received)
        if _t == list or _t == tuple:
            if len(expected) != len(received): return False
            return all(tc_equal(e, r) for (e, r) in zip(expected, received))
        elif _t == float:
            eps = 1e-9
            d = abs(received - expected)
            return not math.isnan(received) and not math.isnan(expected) and d <= eps * max(1.0, abs(expected))
        else:
            return expected == received
    except:
        return False

def pretty_str(x):
    if type(x) == str:
        return '"%s"' % x
    elif type(x) == tuple:
        return '(%s)' % (','.join( (pretty_str(y) for y in x) ) )
    else:
        return str(x)

def do_test(N, __expected):
    startTime = time.time()
    instance = AliceAndBobEasy()
    exception = None
    try:
        __result = instance.make(N);
    except:
        import traceback
        exception = traceback.format_exc()
    elapsed = time.time() - startTime   # in sec

    if exception is not None:
        sys.stdout.write("RUNTIME ERROR: \n")
        sys.stdout.write(exception + "\n")
        return 0

    if tc_equal(__expected, __result):
        sys.stdout.write("PASSED! " + ("(%.3f seconds)" % elapsed) + "\n")
        return 1
    else:
        sys.stdout.write("FAILED! " + ("(%.3f seconds)" % elapsed) + "\n")
        sys.stdout.write("           Expected: " + pretty_str(__expected) + "\n")
        sys.stdout.write("           Received: " + pretty_str(__result) + "\n")
        return 0

def run_tests():
    sys.stdout.write("AliceAndBobEasy (300 Points)\n\n")

    passed = cases = 0
    case_set = set()
    for arg in sys.argv[1:]:
        case_set.add(int(arg))

    with open("AliceAndBobEasy.sample", "r") as f:
        while True:
            label = f.readline()
            if not label.startswith("--"): break

            N = int(f.readline().rstrip())
            f.readline()
            __answer = []
            for i in range(0, int(f.readline())):
                __answer.append(int(f.readline().rstrip()))
            __answer = tuple(__answer)

            cases += 1
            if len(case_set) > 0 and (cases - 1) in case_set: continue
            sys.stdout.write("  Testcase #%d ... " % (cases - 1))
            passed += do_test(N, __answer)

    sys.stdout.write("\nPassed : %d / %d cases\n" % (passed, cases))

    T = time.time() - 1537357569
    PT, TT = (T / 60.0, 75.0)
    points = 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
    sys.stdout.write("Time   : %d minutes %d secs\n" % (int(T/60), T%60))
    sys.stdout.write("Score  : %.2f points\n" % points)

if __name__ == '__main__':
    run_tests()

# }}}
# CUT end
