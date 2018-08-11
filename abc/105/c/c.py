N = int(input())
base = 1
pos = 0
ans = ''
while N != 0:
    if abs(N) & (1 << pos):
        N -= base
        ans += '1'
    else:
        ans += '0'
    pos += 1
    base *= -2
# corner case!
if ans == '':
    print(0)
else:
    print(ans[::-1])
