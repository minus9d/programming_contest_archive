#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import queue

R, C = [int(x) for x in input().split()]
sy, sx = [int(x) - 1 for x in input().split()]
gy, gx = [int(x) - 1 for x in input().split()]

cells = []
for _ in range(R):
    cells.append(input())

q = queue.Queue()
q.put((sy, sx, 0))

seen = set()
seen.add((sy, sx))

while q.qsize():
    y, x, turn = q.get()
    if (y, x) == (gy, gx):
        print(turn)
        break
    else:
        dys = [0, 0, 1, -1]
        dxs = [1, -1, 0, 0]
        for dy, dx in zip(dys, dxs):
            y2, x2 = y + dy, x + dx
            if (y2, x2) in seen:
                continue
            if cells[y2][x2] == '.':
                q.put((y2, x2, turn + 1))
                seen.add((y2, x2))
