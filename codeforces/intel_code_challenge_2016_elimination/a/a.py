#!/usr/bin/env python3
# -*- coding: utf-8 -*-

n = input()
hour,min = map(int,input().split(':'))

if n == "12":
    if not 1 <= hour <= 12:
        hour %= 10
        if hour == 0:
            hour = 10
else:
    if not 0 <= hour <= 23:
        hour %= 10
if not 0 <= min <= 59:
    min %= 10

print("{0:02d}:{1:02d}".format(hour,min))


