#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

def dft(f,n):
    if n == 1:
        return f
    f0 = [ f[2*i + 0] for i in range(n // 2) ]
    f1 = [ f[2*i + 1] for i in range(n // 2) ]
    f0 = dft(f0, n//2)
    f1 = dft(f1, n//2)
    zeta = complex(math.cos(2 * math.pi / n), math.sin(2 * math.pi / n))
    pow_zeta = 1
    for i in range(n):
        f[i] = f0[i % (n//2)] + pow_zeta * f1[i % (n//2)]
        pow_zeta *= zeta
    return f

# http://www.dsprelated.com/showthread/comp.dsp/25408-1.php
def inverse_dft(f,n):
    conj = [x.conjugate() for x in f]
    ffted = dft(conj, n)
    return [x.conjugate() / len(f) for x in ffted]

def pow_2_at_least(n):
    ret = 1
    while True:
        if ret >= n:
            return ret
        else:
            ret *= 2

def padding_zero(array, n):
    return array + [0] * (n - len(array))

def multiply(g, h):
    n = pow_2_at_least(len(g) + len(h) + 1)
    
    g2 = padding_zero(g, n)
    h2 = padding_zero(h, n)

    print("g2: ", g2)
    gg = dft(g2, n)
    print("gg: ", gg)

    hh = dft(h2, n)
    ff = [ gg[i] * hh[i] for i in  range(n) ]
    
    return inverse_dft(ff, n)

def multiply_bf(g, h):
    f = [0] * (len(g) + len(h) - 1)
    for i in range(len(g)):
        for j in range(len(h)):
            f[i+j] += g[i] * h[j]
    return f


def main():
    N = int(input())

    As = []
    Bs = []
    for n in range(N):
        A, B = map(int,input().split())
        As.append(A)
        Bs.append(B)
    # table = multiply_bf(As, Bs)
    table = multiply(As, Bs)

    print(0)
    for i in range(2*N-1):
        print( round(table[i].real) )

main()
