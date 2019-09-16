* 最初に思いついた貪欲→誤り

* 回答を見て、正しい貪欲をPythonで実装 → TLE (https://atcoder.jp/contests/abc140/submissions/7512514)
* これと同じアルゴリズムをC++で再実装 → AC(1511ms) (f.later.vector.cpp)
* アルゴリズムは同じだが、vectorではなくmultisetを使って値の削除が高速にできるように → AC(175ms) (f.later.multiset.cpp)

* 値の削除が起こらない方法をPythonで実装 → AC(638ms) (f.later.py)
