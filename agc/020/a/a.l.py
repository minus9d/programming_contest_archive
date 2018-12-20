# 自力AC
#
# AとBがくっついている状態だと、先に動いたほうが負ける
# AとBがくっついている状態の次に動かなければいけないプレイヤーは、
# AとBとの間の距離によってのみ決まる

N, A, B = map(int, input().split())
if (B - A) % 2:
    print("Borys")
else:
    print("Alice")

