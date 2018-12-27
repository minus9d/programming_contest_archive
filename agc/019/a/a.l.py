Q, H, S, D = map(int, input().split())
N = int(input())

compare2 = [Q*8, H*4, S*2, D]
Q2, H2, S2, D2 = compare2

compare3 = [Q*8, H*4, S*2]
Q3, H3, S3 = compare3

ans = 0
if D2 == min(compare2):
    ans = (N // 2) * D
    N %= 2

if Q3 == min(compare3):
    ans += N * Q * 4
elif H3 == min(compare3):
    ans += N * H * 2
elif S3 == min(compare3):
    ans += N * S

print(ans)
