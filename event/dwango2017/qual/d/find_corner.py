#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import subprocess

filename = 'in.txt'
def make_input():
    with open(filename, 'w') as file:
        n = random.randint(1, 10)
        m = random.randint(1, 10)
        file.write('{} {}\n'.format(n, m))
        for _ in range(n):
            x = random.randint(2, 1000)
            y = random.randint(1, x-1)
            file.write('{} {}\n'.format(x, y))

def main():
    while True:
        make_input()
        myinput = open(filename)
        mine = subprocess.check_output('./a', stdin=myinput, shell=True)
        myinput = open(filename)
        corr = subprocess.check_output('./correct', stdin=myinput, shell=True)
        print("mine, correct = ", mine, corr)
        if mine != corr:
            break
main()


    
