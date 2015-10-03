#!/usr/bin/env python3

import urllib.request, urllib.error, urllib.parse
import time
from random import *
import string
import itertools
import sys, os
import sqlite3
import pickle

# fix me
token = ""


savefile = "dump.pkl"
data = {
    "pairs": {},
    "bests": []
}

def write_pickle():
    with open(savefile, 'wb') as f:
        # シリアライズ
        pickle.dump(data, f)


# 初期化処理
if os.path.exists(savefile):
    with open(savefile, 'rb') as f:
        data = pickle.load(f)
else:
    write_pickle()

def query(url):
    while True:
        try:
            res = urllib.request.urlopen(url)
            break
        except:
            pass
    return res.read()

def get_score(v):
    url    = "https://game.coderunner.jp/query?token=" + token + "&v=" + v
    result = query(url)

    score_num = int(result)
    time.sleep(1)
    return(score_num)

def random_idx(vers):
    while True:
        random_idx = randrange(0,VNUM)
        if not random_idx in vers:
            return random_idx

VNUM = 1000

def main():
    vers = set()
    versList = []
    try_num = 0
    prev = 0
    global data
    print("whats data:",data)

    while True:
        # ランダムに未使用頂点を選ぶ
        v1 = random_idx(vers)
        vers.add(v1)
        versList.append(v1) 
        v2 = random_idx(vers)
        vers.add(v2)
        versList.append(v2)
        
        # 点数調べる
        ret = get_score(",".join(map(str,versList)))
        print("v ", versList, ", ret: ", ret)
    
        # 線分が重なった
        if ret == 0:
            versList = versList[:-2]
            vers = set(versList)
            try_num += 1

            # バグだったかも：ここで最後の2つを消さないといけないはず？？


            # 点数が長い間増えない場合：
            #   そのまま使う 点数の寄与が少ないものを消す or 過去のよいものから選ぶ or ランダムに消す
            if try_num == 10:
                r = randint(0,100)

                # 現在の頂点リストから2つの頂点を消す
                if r < 66:
                    # 点数の寄与が小さいものを消す
                    if r < 33:
                        print("  contribution  ")
                        smallest_score = 10000
                        smallest_idx = -1
                        for i in range(len(vers)//2):
                            score = data["pairs"][(versList[2*i],versList[2*i+1])]
                            print("pair ",i,": ",score)
                            if score < smallest_score:
                                smallest_score = score
                                smallest_idx = i
                        idx = smallest_idx
                    # ランダムに消す
                    else:
                        print("  random  ")
                        idx = random.randrange(lens(vers)//2)

                    versList = versList[:(idx*2)] + versList[(idx*2+2):]
                    vers = set(versList)
                    prev -= smallest_score

                # 過去のよいものから選ぶ
                else:
                    print("  history  ")
                    versList = list((random.choice( data["bests"] ))[1])
                    vers = set(versList)
                    prev = list((random.choice( data["bests"] ))[0])

                try_num = 0

                continue

        # 線分を足すことで点数が増えた
        else:
            try_num = 0
            data["pairs"][(v1,v2)] = ret - prev
            prev = ret
            data["bests"].append((ret, tuple(versList)))
            
            # 上位n個のみ残す
            data["bests"].sort(reverse=True)
            data["bests"] = data["bests"][:10]
            print("data bests num: ", len(data["bests"]))
            write_pickle()

main()

        
            

