// Geminiで出力、一部のみ手で修正

#include <iostream>
#include <vector>

// 実行速度向上のためのおまじない
// (C 標準入出力との同期を切り、cin と cout の結びつきを解除)
void setup_io() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

// long long 型のエイリアス
using ll = long long;

// 制約から、A_i の最大値
// A_i, l, r, y は 0 から 500000 までの値を取る
const int MAX_VAL = 500000;

// フェニック木 (BIT) の構造体
// 0 から MAX_VAL までの「値」をインデックスとして扱う
// 内部的には 1-based indexing で実装するため、サイズは +1 する
struct BIT {
    int n; // BITが管理する値の最大値 + 1 (サイズ)
    std::vector<ll> data;

    // コンストラクタ (サイズ V_max + 1 で初期化)
    BIT(int size) : n(size + 1), data(n + 1, 0LL) {}

    // data[i] に val を加算する (i は 0-indexed の「値」)
    void add(int i, ll val) {
        // 内部では 1-indexed (i+1) に変換して処理
        for (int k = i + 1; k <= n; k += k & -k) {
            data[k] += val;
        }
    }

    // 0 から i までの「値」の合計を返す (i は 0-indexed の「値」)
    ll query(int i) {
        ll sum = 0LL;
        // 内部では 1-indexed (i+1) に変換して処理
        for (int k = i + 1; k > 0; k -= k & -k) {
            sum += data[k];
        }
        return sum;
    }

    // l から r までの「値」の合計を返す (l, r は 0-indexed の「値」)
    ll range_sum(int l, int r) {
        if (l > r) return 0LL;
        // query(r) は [0, r] の和
        // query(l-1) は [0, l-1] の和
        return query(r) - (l == 0 ? 0LL : query(l - 1));
    }
};

int main() {
    setup_io();

    int N, Q;
    std::cin >> N >> Q;

    // A_i の値を保持する配列 (クエリ1での更新に備える)
    std::vector<int> A(N);

    // BITを2本用意する
    // サイズは MAX_VAL + 1 (値 0 から MAX_VAL までを扱うため)
    BIT bit_count(MAX_VAL + 1); // 値 v の個数を管理
    BIT bit_sum(MAX_VAL + 1);   // 値 v の合計 (v * 個数) を管理

    // 初期化
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
        bit_count.add(A[i], 1);
        bit_sum.add(A[i], (ll)A[i]);
    }

    // クエリ処理
    for (int q = 0; q < Q; ++q) {
        int type;
        std::cin >> type;

        if (type == 1) {
            // --- クエリ1: 点更新 ---
            int x, y;
            std::cin >> x >> y;
            // 問題は 1-indexed なので、0-indexed に変換
            x--; 

            int old_val = A[x];

            // 1. 古い値の情報を削除
            bit_count.add(old_val, -1);
            bit_sum.add(old_val, -(ll)old_val);

            // 2. 新しい値の情報を追加
            bit_count.add(y, 1);
            bit_sum.add(y, (ll)y);

            // 3. 配列 A の値を更新
            A[x] = y;

        } else {
            // --- クエリ2: 集計 ---
            int l, r;
            std::cin >> l >> r;

            if (l > r) {
                // このコーナーケースだけ手で追加
                std::cout << (l * N) << "\n";
            }
            else {

                ll ans = 0LL;
    
                // 1. A_i < l の場合 (値は l になる)
                // [0, l-1] の範囲の要素数を取得
                ll count1 = bit_count.range_sum(0, l - 1);
                ans += count1 * (ll)l;
    
                // 2. l <= A_i <= r の場合 (値は A_i のまま)
                // [l, r] の範囲の要素の合計値を取得
                ll total2 = bit_sum.range_sum(l, r);
                ans += total2;
    
                // 3. A_i > r の場合 (値は r になる)
                // [r+1, MAX_VAL] の範囲の要素数を取得
                ll count3 = bit_count.range_sum(r + 1, MAX_VAL);
                ans += count3 * (ll)r;
    
                std::cout << ans << "\n";
            }
        }
    }

    return 0;
}
