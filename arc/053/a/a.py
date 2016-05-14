#!/usr/bin/env python3
# -*- coding: utf-8 -*-
 
幅,高さ = [int(あ) for あ in input().split()]
print((幅-1)*高さ + 幅*(高さ-1))

