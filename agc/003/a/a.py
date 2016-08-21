#!/usr/bin/env python3                                                          
# -*- coding: utf-8 -*-                                                         
 
S = set(input())
if ('S' in S and 'N' not in S) or \
   ('N' in S and 'S' not in S) or \
   ('E' in S and 'W' not in S) or \
   ('W' in S and 'E' not in S):
    print("No")
else:
    print("Yes")
