#!/usr/bin/env python3
# -*- coding: utf-8 -*-

string = 'DiscoPresentsDiscoveryChannelProgrammingContest2016'
W = int(input())

s = 0
e = s + W
while True:
    print(string[s:e])
    s += W
    e += W
    if s >= len(string):
        break
