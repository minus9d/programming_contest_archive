# -*- coding: utf-8 -*-

"""
自分の回答のチェックと、撃墜に使ったファイル
"""

def make(N):
    if N == 1:
        return (737,)
    elif N == 2:
        return (737, 373)
    elif N % 2 == 1:
        ret = []
        ret.append(1 << 28)
        ret.append((1 << 28) + (1 << 27))
        ret.append((1 << 28) + (1 << 26))
        for i in range(N - 3):
            ret.append((1 << 28) + i + 1)
        return tuple(ret)
    else:
        ret = []
        ret.append(1)
        ret2 = list(make(N - 1))
        ret += ret2
        return tuple(ret)

def fast(nums):
    """石numsに対して、winning moveの数を求める
    """
    ans = 0
    for i in range(len(nums)):
        a = 0
        for j in range(len(nums)):
            if j != i:
                a ^= nums[j]
        if nums[i] > a:
            ans += 1
    print("arr len = {}, ans = {}".format(len(nums), ans))
    if len(nums) % 2 == 1:
        if len(nums) != ans:
            print("wrong?")
    else:
        if len(nums) - 1 != ans:
            print("wrong?")
    return ans

for n in range(1, 38):
    arr = make(n)
    fast(arr)


