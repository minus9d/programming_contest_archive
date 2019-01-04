N = int(input())
T, A = map(int, input().split())
Hs = list(map(int, input().split()))

min_dist = 1e10
min_idx = -1
for i, h in enumerate(Hs):
    avg = T - h * 0.006
    if abs(avg - A) < min_dist:
        min_dist = abs(avg - A)
        min_idx = i
print(min_idx + 1)
