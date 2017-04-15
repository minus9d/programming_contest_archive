#!/usr/bin/env python3
# -*- coding: utf-8 -*-

T = int(input())
for testcase in range(T):
    R, C = map(int, input().split())
    cells = []
    for r in range(R):
        cells.append(input())
    # print("\ncells:", cells)

    col_to_letter = []
    for r in range(R):
        tmp = []
        for c in range(C):
            if cells[r][c] != '?':
                tmp.append(c)
        col_to_letter.append(tmp)

    assigns = []
    first = True
    for r in range(R):
        if len(col_to_letter[r]) == 0:
            assigns.append(None)
        else:
            assign = []
            prev = '?'
            yet = True
            first_char = None
            for c in range(C):
                if cells[r][c] != '?':
                    prev = cells[r][c]
                    if yet:
                        first_char = prev
                        yet = False
                assign.append(prev)
            for i in range(len(assign)):
                if assign[i] == '?':
                    assign[i] = first_char
            assigns.append(assign)
    # print("assigns:", assigns)

    first_line = None
    for r in range(R):
        if assigns[r] != None:
            first_line = assigns[r][:]
            break

    print("Case #{}:".format(testcase+1))
    first = True
    for r in range(R):
        if assigns[r] == None:
            if r == 0:
                assigns[r] = first_line[:]
            else:
                assigns[r] = assigns[r-1][:]
        print("".join(assigns[r]))
                
