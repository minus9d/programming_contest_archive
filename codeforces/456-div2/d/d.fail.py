N, M, R, K = [int(x) for x in input().split()]

way = (N - R + 1) * (M - R + 1)

def make_pattern(size, r):
    ret = []
    i = 1
    while size >= 2 and i < r:
        ret.append((i, 2))
        size -= 2
        i += 1
        # print("size, i, r = ", size, i, r)
    ret.append((i, size))
    return ret

pat1 = make_pattern(N, R)
pat2 = make_pattern(M, R)
pat1.reverse()
pat2.reverse()
# print(pat1)
# print(pat2)
point = 0
while K > 0:
    if pat1[0][0] == pat2[0][0]:
        cell_num = pat1[0][1] * pat2[0][1]
        value = pat1[0][0] ** 2
        point += min(cell_num, K) * value
        K -=  min(cell_num, K)

        if pat1[0][0] != 1:
            cell_num = pat1[0][1] * pat2[1][1] \
                     + pat1[1][1] * pat2[0][1]
            value = pat1[0][0] * pat1[1][0]
            point += min(cell_num, K) * value
            K -=  min(cell_num, K)

        pat1 = pat1[1:]
        pat2 = pat2[2:]
    else:
        if len(pat1) > len(pat2):
            longer = pat1
            shorter = pat2
        else:
            longer = pat2
            shorter = pat1
print("{:.15f}".format(way / point))
