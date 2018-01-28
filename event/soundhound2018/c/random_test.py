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
import subprocess
import sys


W, H = 24, 25
for _ in range(100000000):
    with open('random_input.txt', 'w') as file:
        file.write('{} {}\n'.format(H, W))
        for h in range(H):
            s = ''
            for _ in range(W):
                if random.randint(0, 1) % 2:
                    s += '*'
                else:
                    s += '.'
            file.write(s + '\n')
    
    res1 = subprocess.check_output("./a.exe < random_input.txt", shell=True)
    res2 = subprocess.check_output("./correct.exe < random_input.txt", shell=True)
    if res1 != res2:
        sys.exit(0)
    W += 1
    H += 1
