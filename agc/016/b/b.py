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

N = int(input())
As = list(map(int, input().split()))

mn = min(As)
mx = max(As)
if mx > mn + 1:
    print('No')
elif mx == mn:
    if 1 <= mx <= N // 2 or mx == N - 1:
        print('Yes')
    else:
        print('No')
else:
    mn_num = As.count(mn)
    mx_num = As.count(mx)
    k = mn + 1 - mn_num
    # print("can i make {} groups from {}?".format(k, mx_num))
    if mx_num == 0:
        if k == 0:
            print('Yes')
        else:
            print('No')
    else:
        if 1 <= k <= (mx_num // 2):
            print('Yes')
        else:
            print('No')
