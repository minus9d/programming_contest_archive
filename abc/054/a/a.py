
strn = [2,3,4,5,6,7,8,9,10,11,12,13,1]
a, b = map(int, input().split())
a_idx = strn.index(a)
b_idx = strn.index(b)

ans = 'Draw'
if a_idx < b_idx:
    ans = 'Bob'
elif a_idx > b_idx:
    ans = 'Alice'
print(ans)
