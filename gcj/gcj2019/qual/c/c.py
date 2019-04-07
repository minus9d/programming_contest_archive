#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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


def solve2(N, L, ciphertext):

    uniqued_ciphertext = []
    prev = ''
    for c in ciphertext:
        if c != prev:
            uniqued_ciphertext.append(c)
        prev = c

    prime_set = set()
    for i in range(len(uniqued_ciphertext) - 1):
        a = uniqued_ciphertext[i]
        b = uniqued_ciphertext[i + 1]
        p = math.gcd(a, b)
        prime_set.add(p)
        prime_set.add(a // p)
        prime_set.add(b // p)
    if 1 in prime_set:
        prime_set.remove(1)
    primes = list(sorted(prime_set))

    decrypt_map = {}
    prime_num = len(primes)
    for i in range(prime_num):
        for j in range(i, prime_num):
            decrypt_map[primes[i] * primes[j]] = (primes[i], primes[j])

    p2char = {}
    for i, prime in enumerate(sorted(primes)):
        p2char[prime] = chr(ord('A') + i)

    def try_decrypt(first):
        ans = p2char[first]
        prev = first
        for t in ciphertext:
            if t % prev != 0:
                raise ValueError
            t //= prev
            ans += p2char[t]
            prev = t
        return ans

    for t in ciphertext:
        two_primes = decrypt_map[t]
        try:
            return try_decrypt(two_primes[0])
        except Exception:
            return try_decrypt(two_primes[1])

def solve():
    N, L = map(int, input().split())
    ciphertext = list(map(int, input().split()))
    print(solve2(N, L, ciphertext))



# for debug
# def make_primes(N):
#     primes = [2]
#     for i in range(3, N + 1):
#         is_prime = True
#         for p in primes:
#             if i % p == 0:
#                 is_prime = False
#                 break
#         if is_prime:
#             primes.append(i)
#     return primes


# random.seed(777)
# N = 10000
# primes = make_primes(N)[1:]
# while True:
#     chosen_primes = list(sorted(random.sample(primes, 26)))

#     text = list(range(26))
#     text += random.choices(list(range(26)), k=10)
#     random.shuffle(text)

#     ciphertext = []
#     for i in range(len(text) - 1):
#         ciphertext.append(chosen_primes[text[i]] * chosen_primes[text[i + 1]])

#     ans = solve2(N, len(ciphertext), ciphertext)
#     text2 = ''.join([chr(ord('A') + i) for i in text])
#     if ans != text2:
#         print("error!!")
#         print("text2 = ", text2)
#         print("ans = ", ans)
#         sys.exit(0)
#     print("ok")



T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
