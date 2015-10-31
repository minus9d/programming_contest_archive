#!/usr/bin/env python3

import urllib.request, urllib.error, urllib.parse
import time
import math
from random import *
import string
import itertools
import sys, os
import sqlite3
import pickle

# fix me
token = ""

URL = "http://game.coderunner.jp/"

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
            time.sleep(0.01)
            pass
    return res.read()

def enter():
    url = URL + "enter?" + token
    txt = query(url)
    return txt

def parse_info(txt):
    lines = txt.splitlines()

    ret = {}
    att, damage = lines[0].split()
    ret["att"] = att
    ret["damage"] = damage

    hp, ini_hp = lines[1].split()
    enemy_num = int(lines[2])
    print("enemy num:", enemy_num)

    hps = []
    for i in range(enemy_num):
        hps.append(int(lines[3 + i]))
    print("hps:",hps)
    
    usr1,att1,damage1 = lines[3 + enemy_num].split()
    usr2,att2,damage2 = lines[4 + enemy_num].split()

    event_num = int(lines[5 + enemy_num])
    print("event num:",event_num)
    for i in range(event_num):
        usr,eid,t,hp = lines[6 + enemy_num].split()

    print(ret)



# txt = """2604996 40599634
# 13879712 39050001
# 3
# 10857025
# 17480761
# 27899524
# PlayerB 1542564 72452052
# PlayerC 1522756 52232156
# 3
# PlayerC 4 5017 39050001
# PlayerB 5 5017 25158831
# PlayerA 5 4265 43349056
# """
# print(txt)

# parse_info(txt)

# txt = """{"power":2604996,"damage":40599634,"hp":13879712,"maxhp":39050001,"hps":[10857025,17480761,27899524],"friend":[{"id":"PlayerB","power":1542564,"damage":72452052},{"id":"PlayerC","power":1522756,"damage":52232156}],"log":[{"id":"PlayerC","enemy":4,"time":5017,"hp":39050001},{"id":"PlayerB","enemy":5,"time":5017,"hp":25158831},{"id":"PlayerA","enemy":5,"time":4265,"hp":43349056}]}"""

import json
def parse_info_json(txt):
    ret = json.loads(txt.decode('utf-8'))
    return ret

def get_info_json():
    url    = URL + "infoJson?" + token
    txt = query(url)
    return txt

def get_rank(userid):
    if who == None:
        url = URL + "myrank?" + token
    else:
        url = URL * "rank?uid=" + userid
    txt = query(url)
    return(txt)

def get_history(roomid):
    url = URL + "room?rid=" + roomid
    txt = query(url)
    return(txt)


def main():
    
    while True:

        res = enter()
        print("res:",res)
        if res == b'GAME START':
            print("start!")

        is_first = True

        # in game
        while True:
            info_txt = get_info_json()
            # print("info_txt:",info_txt)

            if info_txt == b'OUT ROOM':
                print("out room")
                break

            info = parse_info_json(info_txt)
            # print("info:",info)

            d1 = info["damage"]
            d2 = info["friend"][0]["damage"]
            d3 = info["friend"][1]["damage"]
            hp = info["hp"] + sum(info["hps"])
            hp_initial = hp + d1 + d2 + d3

            print("enemies initial hp:")
            print(" ", hp_initial)

            print("enemies remained hp:")
            print(" ", hp, "(", hp / hp_initial * 100, ")")

            print("damages:")
            print(" ", d1, "(", d1 / hp_initial * 100, ")")
            print(" ", d2, "(", d2 / hp_initial * 100, ")")
            print(" ", d3, "(", d3 / hp_initial * 100, ")")

            t1 = math.sqrt(info["power"])
            t2 = math.sqrt(info["friend"][0]["power"])
            t3 = math.sqrt(info["friend"][1]["power"])
            hp = info["hp"]

            print("next enemies:")
            hps = info["hps"]
            hps_rate = [hp / hp_initial for hp in hps]
            print(" ", list(zip(hps, hps_rate)))

            print("current enemy:")
            print(" ", hp, "(", hp / hp_initial, ")")
            
            # if order is fixed, attack
            if (d1 / hp_initial > 0.5):
                res = enter()
                print("res:",res)
                continue


            # if next enemy has bigger hp, wait
            if len(hps) > 0 and hps[0] > hp * 1.5:
                print("wait for others to attack")
                continue

            print("t1,t2,t3,hp=",t1,t2,t3,hp)
            a = 3
            b = t1+t2+t3
            c = t1**2 + t2**2 + t3**2 - hp
            D = b**2 - a * c
            if D <= 0:
                res = enter()
                print("res:",res)
            else:
                T = (-b + math.sqrt(D)) / a
                if T <= 0:
                    res = enter()
                    continue
                else:
                    print("T:",T)

                    # time.sleep(T/1000.0)
                    # time.sleep(0.1)

                    # res = enter()
                    # print("res:",res)

main()

        
            

