A, B, C = map(int, input().split())
ans = 0

mn = min(A, C)
ans += mn
A -= mn
C -= mn

mn = min(B, C)
ans += 2 * mn
B -= mn
C -= mn
if C > 0:
    ans += 1
elif B > 0:
    ans += B
print(ans)
