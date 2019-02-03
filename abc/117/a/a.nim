# 参考: https://qiita.com/Kutimoti_T/items/635bacddfa1304de40db

import strutils
import sequtils

proc getInts() : seq[int] = 
    readLine(stdin).split().map(parseInt)

var tx = getInts()
echo tx[0] / tx[1]

