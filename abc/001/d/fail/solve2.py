#!/usr/bin/env python
# -*- coding: utf-8 -*-

seenAsMid = {}
seenAsStart = {}
seenAsEnd = {}
    
N = int(input())
for i in range(0, N):
    (start, end) = map(int, input().split('-'))
    start -= (start % 5)
    end += (5 - (end % 5)) % 5

    for i in range(start, end+1, 5):
        
        if i == start:
            seenAsStart[ i//5 ] = True
        if i == end:
            seenAsEnd[ i//5 ] = True
        if i != start and i != end:
            seenAsMid[ i//5 ] = True # // は Cの/と同じ

isContinue = False
start = 0
end = 0
for i in range(0, 2400//5+1):
    if i in seenAsStart and (not i in seenAsMid and not i in seenAsEnd):
        start = i
    elif i in seenAsEnd and (not i in seenAsMid and not i in seenAsStart):
        end = i
        print ("%04d-%04d" % (start*5, end*5))
