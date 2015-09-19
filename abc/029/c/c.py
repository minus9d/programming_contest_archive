#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from  itertools import *
n = int(input())
for c in product("abc",repeat = n):
    print("".join(c))

