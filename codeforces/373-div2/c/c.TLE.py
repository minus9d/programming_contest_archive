#!/usr/bin/env python3
# -*- coding: utf-8 -*-

n, t = map(int, input().split())
num_s = input()
dot_pos = num_s.find('.')
num_s = num_s.replace('.', '')
num_s = list(map(int, num_s))

def roundupint(s, pos):
    s = list(map(int, s))
    ans = s[:]

    for i in range(pos+1, len(s)):
        ans[i] = 0
    if ans[pos] != 9:
        ans[pos] += 1
    else:
        ans[pos] = 0
        carry = 1
        for i in range(pos-1, -1, -1):
            ans[pos] += carry
            if ans[pos] == 10:
                ans[pos] = 0
                carry = 1
            else:
                carry = 0
        if carry == 1:
            ans = [1] + ans
    return ans

while t > 0:
    changed = False
    for i, ch in enumerate(num_s):
        if i < dot_pos:
            continue
        ch_n = int(ch)
        if ch_n >= 5:
            num_s = roundupint(num_s, i-1)
            changed = True
            t -= 1
            break

    if not changed:
        break

# print("dot_pos:", dot_pos)
# print("n:", n)
num_s.insert(dot_pos - n + 1, '.')
# print("num_s:", num_s)
ans = ''.join(map(str, num_s))
ans = ans.rstrip('0')
if ans[-1] == '.':
    ans = ans[:-1]
print(ans)




