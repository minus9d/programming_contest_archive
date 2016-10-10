#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import random

n = 80000
nums = random.sample(range(1, 100000000), n)

print(n)
print(" ".join(map(str,nums)))

