#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair


void do_unique(string& s){
    s.erase( unique(ALL(s)), s.end() );
}

bool invalid_word(string str)
{
    auto str2 = str;
    sort(ALL(str2));
    do_unique(str2);
    return SIZE(str) != SIZE(str2);
}

string find_word(vector<string>& strs, char h_ch)
{
    for(auto s : strs) {
        if (s[0] == h_ch && SIZE(s) > 1) return s;
    }
    return "";
}

const ll MOD = 1000000007;
ll fact(int N) {
    ll ret = 1;
    FOR(n, 1, N+1) {
        ret *= n;
        ret %= MOD;
    }
    return ret;
}

ll solve(vector<string>& strs, int N)
{
    // abaのような語があれば即終了
    for(auto& str : strs){
        // cout << "str: " << str << endl;
        if (invalid_word(str)) return 0;
    }

    // 文字の出現場所をカウント
    map<char, int> begin_ch;
    map<char, int> end_ch;
    map<char, int> middle_ch;
    map<char, int> single_ch;
    for(auto& str : strs){
        auto len = SIZE(str);
        if (len == 1) {
            ++single_ch[ str[0] ];
        }
        else if (len == 2) {
            ++begin_ch[ str[0] ];
            ++end_ch[ str[1] ];
        }
        else {
            ++begin_ch[ str[0] ];
            ++end_ch[ str[ len-1 ] ];
            FOR(i, 1, len-1) {
                ++middle_ch[ str[i] ];
            }
        }
    }

    // cout << "begin: ";
    // for (auto& p : begin_ch) {
    //     if (p.second > 0) cout << p.first << ", ";
    // }
    // cout << endl;
    // cout << "end: ";
    // for (auto& p : end_ch) {
    //     if (p.second > 0) cout << p.first << ", ";
    // }
    // cout << endl;

    // 真ん中の文字は、他の場所に現れられない
    for (auto& p : middle_ch) {
        auto m_ch = p.first;
        if (begin_ch[ m_ch ] || end_ch[ m_ch ] || single_ch[ m_ch ]) return 0;
    }

    // 同じ文字が2回以上頭や末尾に現れられない
    REP(i, 26) {
        char ch = 'a' + i;
        if (begin_ch[ch] > 1 || end_ch[ch] > 1) return 0;
    }

    // グループを作っていく
    set<string> seen;
    int group_num = 0;
    for (auto& p : begin_ch) {
        auto h_ch = p.first;
        if (p.second == 0) continue;
        
        if (end_ch[ h_ch ] > 0) continue;

        bool found = false;
        while (1) {
            auto word = find_word(strs, h_ch);
            if (word == "") break;
            if (seen.count(word)) break;
            found = true;
            seen.insert(word);
            h_ch = word[ SIZE(word) - 1 ];
        }

        if(found) ++group_num;
    }

    // 他の語の先頭・末尾に現れない単独文字もグループを形成する
    for (auto& p : single_ch) {
        auto m_ch = p.first;
        auto count = p.second;
        if (count > 0 && begin_ch[ m_ch ] == 0 && end_ch[ m_ch ] == 0) {
            ++group_num;
        }
    }

    // グループ化に失敗した長さ2以上の語があれば失敗
    // 例： ca と abc が集合に含まれているときに起こる
    for (auto& s : strs){
        if (SIZE(s) == 1) continue;
        if (seen.count(s) == 0) {
            return 0;
        }
    }

    ll ret = 0;
    // cout << "group_num " << group_num << endl;
    ret = fact(group_num);
    ret %= MOD;
    // {a, a, a, abc}の場合3!をかける
    for (auto& p : single_ch) {
        ret *= fact(p.second);
        ret %= MOD;
    }

    return ret;
}

int main(void)
{
    int TEST_NUM;
    cin >> TEST_NUM;

    for(int test = 0; test < TEST_NUM; ++test){
        int N;
        cin >> N;
        vector<string> strs(N);
        REP(n, N){
            cin >> strs[n];
            do_unique(strs[n]);
        }

        auto ret = solve(strs, N);
        
        cout << "Case #" << (test+1) << ": " << ret << endl;
    }

    return 0;
}
