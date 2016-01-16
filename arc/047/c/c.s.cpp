// http://stackoverflow.com/questions/31216097/given-n-and-k-return-the-kth-permutation-sequence

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
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
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair
#define mt make_tuple

void find(ll n, ll k)
{
    vector<ll> numbers(n);
    vector<ll> indices(n);
    REP(i,n) numbers[i] = i + 1;
    ll divisor = 1;
    for (ll place = 1; place <= n; place++)
    {
        if((k / divisor) == 0)
            break;  // all the remaining indices will be zero

        // compute the index at that place:
        indices[n-place] = (k / divisor) % place;
        divisor *= place;
    }

    // print out the indices:
    // System.out.println(Arrays.toString(indices));

    // permute the numbers array according to the indices:
    REP(i,n)
    {
        ll index = indices[i] + i;

        // take the element at index and place it at i, moving the rest up
        if(index != i)
        {
            ll temp = numbers[index];
            for(ll j = index; j > i; j--)
               numbers[j] = numbers[j-1];
            numbers[i] = temp;
        }
    }
    REP(i,n) cout << numbers[i] << endl;
}
    

int main(void)
{
    cin.sync_with_stdio(false);
    ll N, K;
    cin >> N >> K;

    ll query = 1;
    REP(n,N) query *= (n + 1);
    query /= K;

    find(N, query-1);

    return 0;
}
