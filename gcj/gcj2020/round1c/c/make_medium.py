#!/usr/bin/env python3

import random

def print_set2():

    T = 100
    print(T)
    
    for t in range(T):
        N = 5
        D = random.randint(2, 50)
        print(N, D)
        As = []
        for n in range(N):
            # As.append(random.randint(1, 360 * 10**9))
            As.append(random.randint(1, 360))
        print(*As)

print_set2()

