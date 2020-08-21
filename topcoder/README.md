### TopCoder

* 解説へのリンク
  * [Data Science Editorials – topcoder](https://www.topcoder.com/community/data-science/data-science-editorials/)
  * [Algorithm Problem Set Analysis - TopCoder Wiki (obsolete?)](http://apps.topcoder.com/wiki/display/tc/Algorithm+Problem+Set+Analysis)


### TCO

| No. |One|Two|Three|
|:---:|:-:|:-:|:-:|
| TCO15R1C |◎|×問題理解できず|-|
| TCO15R2B |□ 期待値|-|-|
| TCO15R2C |×|-|-|
| TCO16R1A |◎|◎|-|
| TCO17R1A |◎|〇|-|
| TCO18R1B |◎|〇|〇|

| 問題 | status | 問題概要 | コメント |
|:---:|:-:|:-|:-|
| TCO19 Round 1B easy | ◎ | | |
| TCO19 Round 1B med  | □ | 足場を移動してコインを取得。最初の足場を選んでコイン枚数を最大化 | O(N^2)やるだけだけど定数倍に注意 |

| 問題 | status | 問題概要 | コメント |
|:---:|:-:|:-|:-|
| TCO20 Round 1B easy | ◎ | | ★怪しいbitDPで時間浪費。実際は配列の長さだけで勝敗が決まる! |

| 問題 | status | 問題概要 | コメント |
|:---:|:-:|:-|:-|
| TCO20 Round 3B easy | ◎ | 最大3個の障害物が与えられる。盤面の半分以上をたどる経路を一つ返す | すぐさまDFSを書いてACしたが実は運が良かっただけ。https://twitter.com/minus9d/status/1296421651261816833 |



### Div. 1

| No. |One|Two|Three|
|:---:|:-:|:-:|:-:|
| 665-Div1 |×LuckySum|-|-|
| 679-Div1 |◎|×|×|
| 683-Div1 |◎|×|×|
| 687-Div1 |◎|×|×|
| 704-Div1 |○|×|×|
| 708-Div1 |×問題文読み間違い|×|×|
| 711-Div1 |◎|×|×|
| 730-Div1 |○木DP、memo化を忘れてTLE|×|×|

| 問題 | status | 問題概要 | コメント |
|:---:|:-:|:-|:-|
| TCO19 SRM 737 easy | ◎ | 先攻が勝利できる手数が最大になるようNimの山を構成 | 実験でぎりぎり解けた、あとから証明を理解 |
| TCO19 SRM 737 med  |- |  |  |
| TCO19 SRM 737 hard |- |  |  |
| TCO19 SRM 749 easy |◎|  |オーバーフローに気を付けて二分探索|
| TCO19 SRM 749 med  |- |  |  |
| TCO19 SRM 749 hard |- |  |  |
| TCO19 SRM 752 easy |◎|`<>=!`を成り立たせる最小の文字列を生成|DFSで解けたが一般にはDPらしい|
| TCO19 SRM 752 med  |- |  |  |
| TCO19 SRM 752 hard |- |  |  |
| TCO19 SRM 759 easy |◎|各桁の和がsumsになる5桁の素数3つを返す|  |
| TCO19 SRM 759 med  |- |  |  |
| TCO19 SRM 759 hard |- |  |  |

#### SRM 788

| 問題 | status | 問題概要 | コメント |
|:---:|:-:|:-|:-|
| easy |□| |MST。多重辺があるのを知らなくてWA|
| med  |○| |初めてmedを本番AC| 
| hard |- | | |


### Div. 2

| No. |One|Two|Three|
|:---:|:-:|:-:|:-:|
| 669-Div2 |◎|◎|×MST|
| 675-Div2 |◎|◎ダイクストラ亜種、要復習|-|
| 712-Div2 |◎|◎|×|
| 722-Div2 |◎|×|×|
| 735-Div2 |◎|◎|□★ある文字が大多数を占めるような部分数列の数を求める|
