#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
a, d = map(int, input().split())
M = int(input())
data = {}

def get_i(data, i):
    if i in data:
        return data[i]
    else:
        return a + d * i

def data_swap(y, z, data):
    tmp = get_i(data, y)
    data[y] = get_i(data, z)
    data[z] = tmp

def data_write(y, z, data):
    data[y] = get_i(data, z)

for m in range(M):
    # for i in range(5):
    #     print(get_i(data, i))
    # print("---")

    x, y, z = map(int, input().split())
    y -= 1
    z -= 1
    if x == 0:
        data_swap(y, z, data)
    else:
        data_write(y, z, data)

K = int(input())
print(get_i(data, K-1))
