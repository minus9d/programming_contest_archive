#!/usr/bin/env python3
# -*- coding: utf-8 -*-


seen = [False] * 24 * 60

def getMin(num):
    return (num//100) * 60 + num % 100

def MinToHourMin(min):
    hour = min // 60
    min %= 60
    return "{0:02d}{1:02d}".format(hour, min)
    
N = int(input())

record = []

for i in range(0, N):
    (start, end) = map(int, input().split('-'))

    start = getMin(start)
    end = getMin(end)
    
    start -= (start % 5)
    end += (5 - (end % 5)) % 5

    # ソートした時に開始時刻の方が先に来るようにするために、開始時刻の方を-1にする
    # もし逆にしてしまうと、開始時刻と終了時刻が同じになる場合に失敗する
    record.append( (start, -1) )
    record.append( (end, 1) )

record.sort()

counter = 0
for r in record:
    (time, flag) = r
    if counter == 0:
        print(MinToHourMin(time), end='')
    counter += flag
    if counter == 0:
        print('-' + MinToHourMin(time))
