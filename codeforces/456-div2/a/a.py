yc, bc = [int(x) for x in input().split()]
yb, gb, bb = [int(x) for x in input().split()]

ans = 0
if yc < yb * 2:
    ans += yb * 2 - yc
    yc = 0
else:
    yc -= yb * 2

if bc < bb * 3:
    ans += bb * 3 - bc
    bc = 0
else:
    bc -= bb * 3

if yc < gb:
    ans += gb - yc
if bc < gb:
    ans += gb - bc

print(ans)
