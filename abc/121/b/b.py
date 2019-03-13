N, M, C = map(int, input().split())
Bs = list(map(int, input().split()))
ans = 0
for n in range(N):
  As = list(map(int, input().split()))
  score = C
  for a, b in zip(As, Bs):
    score += a * b
  ans += score > 0
print(ans)
