# 自力AC
#
# 後ろから順に考える
# 最後のA_Kは必ず2である必要がある
# A_Kの前には2~3人である必要がある
# ...

K = int(input())
As = list(map(int, input().split()))
As.reverse()

fail = False
if As[0] != 2:
    fail = True
else:
    mn = 2
    mx = 3
    for a in As[1:]:
        # 今 [mn, mx] = [4, 13], a = 3だとする
        # a人組をつくったあとにありうる数は3の倍数であり、この場合3, 6, 9, 12。
        # 以下のコードでmn = 3, mx = 12を求める
        if mn % a != 0:
            mn = (mn // a) * a + a
        if mx % a != 0:
            mx = (mx // a) * a
        if mn > mx:
            fail = True
            break

        # a人組をつくるまえにありうる数を考えると, mnはそのまま
        # mxはaにより切り捨てられる分だけ大きくできる
        mx = mx + (a - 1)
if fail:
    print(-1)
else:
    print(mn, mx)
