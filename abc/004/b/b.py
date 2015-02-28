#!/usr/bin/env python3
# -*- coding: utf-8 -*-

mat = []
for i in range(4):
    mat.append( list(input().split()) )
for j in range(3, -1, -1):
    print( " ".join(mat[j][::-1]) )

