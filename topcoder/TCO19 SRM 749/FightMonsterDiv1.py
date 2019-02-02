#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import array
from bisect import *
from collections import *
import fractions
import heapq
from itertools import *
import math
import re
import string

class FightMonsterDiv1:
    def regular_N_damage(self, N):
        base = N * self.attack
        sub = self.attack * self.level * (N - 1) * N // 200
        return base + sub

    def check1(self, k):
        damage = self.regular_N_damage(k)
        return damage >= self.hp

    def check2(self, k):
        if self.duration > k - 1:
            damage = self.regular_N_damage(k - 1) * 5
            return damage >= self.hp
        else:
            damage1 = self.regular_N_damage(k - self.duration - 1)
            damage2 = (self.regular_N_damage(k - 1) - damage1) * 5
            damage = damage1 + damage2
            return damage >= self.hp

    def fightTime(self, hp, attack, level, duration):
        self.hp = hp
        self.attack = attack
        self.level = level
        self.duration = duration

        lo = 0
        hi = int(1e10)
        while lo < hi:
            k = (lo + hi) // 2
            if self.check1(k):
                hi = k
            else:
                lo = k + 1
        ans1 = lo

        lo = 0
        hi = int(1e10)
        while lo < hi:
            k = (lo + hi) // 2
            if self.check2(k):
                hi = k
            else:
                lo = k + 1
        ans2 = lo

        return min(ans1, ans2)

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

def do_test(hp, attack, level, duration, __expected):
    startTime = time.time()
    instance = FightMonsterDiv1()
    exception = None
    try:
        __result = instance.fightTime(hp, attack, level, duration);
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
    sys.stdout.write("FightMonsterDiv1 (250 Points)\n\n")

    passed = cases = 0
    case_set = set()
    for arg in sys.argv[1:]:
        case_set.add(int(arg))

    with open("FightMonsterDiv1.sample", "r") as f:
        while True:
            label = f.readline()
            if not label.startswith("--"): break

            hp = int(f.readline().rstrip())
            attack = int(f.readline().rstrip())
            level = int(f.readline().rstrip())
            duration = int(f.readline().rstrip())
            f.readline()
            __answer = int(f.readline().rstrip())

            cases += 1
            if len(case_set) > 0 and (cases - 1) in case_set: continue
            sys.stdout.write("  Testcase #%d ... " % (cases - 1))
            passed += do_test(hp, attack, level, duration, __answer)

    sys.stdout.write("\nPassed : %d / %d cases\n" % (passed, cases))

    T = time.time() - 1549109732
    PT, TT = (T / 60.0, 75.0)
    points = 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
    sys.stdout.write("Time   : %d minutes %d secs\n" % (int(T/60), T%60))
    sys.stdout.write("Score  : %.2f points\n" % points)

if __name__ == '__main__':
    run_tests()

# }}}
# CUT end
