
# シミュレーションすると
#   0: a b c
#   1: b+c     c+a     a+b            ans = b-a
#   2: 2a+b+c  a+2b+c  a+b+2c         ans = a-b
#   3: 2a+3b+3c  3a+2b+3c  3a+3b+2c       
# 整数の差には簡単な規則性がある

A, B, C, K = map(int, input().split())
if K % 2 == 1:
    print(B - A)
else:
    print(A - B)


