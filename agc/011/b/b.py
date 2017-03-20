N = int(input())
As = list(map(int, input().split()))
As.sort()

s = 0
ans = 0
for i in range(len(As)-1):
	s += As[i]
	if s * 2 >= As[i+1]:
		ans += 1
	else:
		ans = 0
ans += 1
print(ans)
