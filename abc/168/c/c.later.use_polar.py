#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
import cmath

A, B, H, M = map(int, input().split())

def rate_to_arg(rate):
    return - 2 * math.pi * rate

short_rate = (H * 60 + M) / 720
long_rate = M / 60

short = 0 + A * 1j
short *= cmath.rect(1.0, rate_to_arg(short_rate))

long = 0 + B * 1j
long *= cmath.rect(1.0, rate_to_arg(long_rate))

print("{:.20f}".format(abs(long - short)))


