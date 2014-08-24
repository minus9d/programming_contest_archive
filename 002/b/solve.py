#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re

W = input()
W = re.sub(r'[aeiou]', '', W)
print (W)
