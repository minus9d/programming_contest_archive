#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def solve():
    first = input()
    second = input()
    
    days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    names = ["monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"]
    
    for offset in range(7):
        cnt = offset
        records = [ names[cnt] ]
        for m in range(11):
            cnt += days[m]
            records.append( names[cnt % 7] )
            if records[-2:] == [first,second]:
                return "YES"
    return "NO"

print(solve())
            
        
