#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define FOREACH(i, n) for (__typeof((n).begin()) i = (n).begin(); i != (n).end(); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

int main(void)
{
    int T;
    cin >> T;

    REP(t, T){
        
        ll E, R, N;
        cin >> E >> R >> N;
        vector<ll> values(N);
        vector<pair<ll, ll> > sorted_values(N);
        vector<ll> max_possible_energies(N);
        vector<ll> min_leave_energies(N);

        REP(i, N){
            ll val;
            cin >> val;
            values[i] = val;
            max_possible_energies[i] = E;
            min_leave_energies[i] = 0;
            sorted_values[i] = make_pair( val, i );
        }
        
        sort(sorted_values.begin(), sorted_values.end(), greater<pair<ll, ll> >());

        ll ret = 0;
        FOREACH(p, sorted_values){
            ll val = p->first;
            ll index = p->second;

            ll offset = 1;
            while(index + offset < N){
                max_possible_energies[index + offset]
                    = min(max_possible_energies[index + offset]
                          , max(0LL, offset * R));
                ++offset;
            }
            offset = -1;
            while(index + offset >= 0){
                min_leave_energies[index + offset]
                    = max(min_leave_energies[index + offset]
                          , max(0LL, E + offset * R));
                --offset;
            }

            ll use_energy
                =  max(0LL, max_possible_energies[index] - min_leave_energies[index]);

            ret += use_energy * values[index];
        }

        cout << "Case #" << (t+1) << ": " << ret << endl;
    }

    return 0;
}
