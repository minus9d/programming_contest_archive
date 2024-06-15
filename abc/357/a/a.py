N, M = map(int, input().split())
H = list(map(int, input().split()))

ans = 0
for i in range(N):
    h = H[i]
    if M >= h:
        M -= h
        ans += 1
    else:
        break
print(ans)
