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

for N in range(1010, 2001):
    print(N)

    balls = []
    for n in range(N):
        balls.append(('B', n + 1))
        balls.append(('W', n + 1))

    for _ in range(1):
        random.shuffle(balls)            

        with open('random_input.txt', 'w') as file:

            file.write('{}\n'.format(N))
            for ball in balls:
                file.write('{} {}\n'.format(*ball))
    
        res1 = subprocess.check_output("./a.exe < random_input.txt", shell=True)
        res2 = subprocess.check_output("./correct.exe < random_input.txt", shell=True)
        if res1 != res2:
            print("error! my ans {}, correct ans {}".format(res1, res2))
            sys.exit(0)

    


    
