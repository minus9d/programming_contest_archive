#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <map>
using namespace std;

typedef long long ll;

void getPrimes(ll n, vector<ll>&primes)
{
	vector<ll>::iterator itr;
	map<ll, int> isNotPrime;

	for (ll i = 2; i < n; i++)
	{
		if (i == 2)
		{
			primes.push_back(i);
		}
		
		else if(i % 2 != 0 && !isNotPrime[i])
		{
			//printf("prime = %lld\n", i);
			primes.push_back(i);
			ll num = i;
			while(num <= n)
			{
				isNotPrime[num] = 1;
				num += i;
			}
		}
	}
}

int main(int ARGC, char *ARGV[])
{
	ll Nmax = 1000000000000;
	ll max = 1000001;
	//ll Nmax = 10000000000;
	//ll max = 100000;
	vector<ll>primes;
	getPrimes(max, primes);
	printf("end.\n");

	vector<ll>::iterator itr;
	set<ll>keys;
	vector<ll>keys2;
	for (itr = primes.begin(); itr != primes.end(); itr++)
	{
		ll prime = *itr;
		ll num = prime * prime;
		while (num <= Nmax)
		{
			//keys.insert(num);
			keys2.push_back(num);
			num *= prime;
		}
	}
	//keys.insert(2);
	keys2.push_back(2);

	std::sort(keys2.begin(), keys2.end());
	printf("end.\n");
	printf("size = %lld\n", keys2.size());

	std::ifstream ifs( ARGV[1] );

	int testcaseNum;
	ifs >> testcaseNum;
	for (int t = 0; t < testcaseNum; t++)
	{
		ll N;
		ifs >> N;
		ll ans;

		while(1)
		{
			set<ll>::iterator pos = keys.find( N );
			if (pos == keys.end())
			{
				N--;
			}
			else
			{
				ans = *pos + 1;
			}
		}

		printf("Case #%d: %d\n", t + 1, ans);
		

	}

	return 0;
}
