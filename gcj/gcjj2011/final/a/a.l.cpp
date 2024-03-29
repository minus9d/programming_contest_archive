#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;


void solve(void)
{
	double pi = 3.14159265359;
	static int qNo = 1;
	int K;
	cin >> K;

	vector<int> es;
	for (int k = 0; k < K; k++) {
		int num;
		cin >> num;
		es.push_back(num);
	}

	sort(es.begin(), es.end(), greater<int>());

	//double ans = 0.0;
	//for (int i = 0; i < K - 1; i++)
	//{
	// ans += es[i] * es[i + 1];
	//}
	//ans += es[0] * es[K-1];

	vector<int> list;
	list.resize( es.size() );
	int idx = es.size() / 2;
	int moveDist = 1;
	int moveDir = -1;
	for (int i = 0; i < K; i++)
	{
		list[ idx ] = es[i];
		idx += moveDist * moveDir;
		moveDir *= -1;
		moveDist++;
	}

	double ans = 0.0;
	for (int i = 0; i < K - 1; i++)
	{
		ans += list[i] * list[i + 1];
	}
	ans += list[0] * list[K-1];

	//sort(es.begin(), es.end());
	//double ansMax = 0.0;
	//do {
	//	double ansTemp = 0.0;
	//	for (int i = 0; i < K - 1; i++)
	//	{
	//		ansTemp += es[i] * es[i + 1];
	//	}
	//	ansTemp += es[0] * es[K-1];
	//	if (ansTemp > ansMax) {
	//		ansMax = ansTemp;
	//	}
	//} while (next_permutation(es.begin(), es.end()));

	printf("Case #%d: %10.9lf\n", qNo++, ans / 2.0 * sin(2 * pi / K));
	//printf("Case #%d: %10.9lf\n", qNo++, ansMax / 2.0 * sin(2 * pi / K));
}

int main(void)
{
	int N;
	scanf("%d", &N);

	for(int n = 0; n < N; n++) {
		solve();
	}
	return 0;
}
