cdef int N, n
cdef unsigned long long ans

N = int(input())
ans = 0
for n in range(1, N + 1):
  if n % 3 != 0 and n % 5 != 0:
    ans += n
print(ans)
