#!/usr/bin/env python3
# -*- coding: utf-8 -*-

S = input()
year = int(S[:4])
month = int(S[5:7])
day = int(S[8:])

heisei_flag = False
if year < 2019:
   heisei_flag = True
else:
    if month <= 4:
       heisei_flag = True
if heisei_flag:
   print('Heisei')
else:
   print('TBD')    
