# 自力AC
#    3 4 5 6などと連続する最長列を探す


N = int(input())
Ps = []
for n in range(N):
    Ps.append(int(input()))

counter = [0] * (N + 1)

for p in Ps:
    counter[p] = counter[p-1] + 1

ans = 0
for c in counter:
    ans = max(ans, c)
print(N - ans)
