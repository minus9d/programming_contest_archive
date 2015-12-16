#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int solve(string *sides, int *locations, int size)
{
	int time = 0;
	int orangeLocation = 1;
	int blueLocation = 1;
	int orangeWaitingTime = 0;
	int blueWaitingTime = 0;

	for (int i = 0; i < size; i++)
	{
		if (sides[i] == "B")
		{
			int distance = abs(locations[i] - blueLocation);

			if (distance <= blueWaitingTime)
			{
				distance = 0;
			}
			else
			{
				distance -= blueWaitingTime;
			}

			time += (distance + 1);

			blueLocation = locations[i];
			orangeWaitingTime += (distance + 1);
			blueWaitingTime = 0;
		}
		else
		{
			int distance = abs(locations[i] - orangeLocation);
			if (distance <= orangeWaitingTime)
			{
				distance = 0;
			}
			else
			{
				distance -= orangeWaitingTime;
			}

			time += (distance + 1);

			orangeLocation = locations[i];
			orangeWaitingTime = 0;
			blueWaitingTime += (distance + 1);
		}
	}
	return time;
}

int main (int ARGC, char *ARGV[])
{
	std::ifstream ifs( ARGV[1] );

	int testcaseNum;
	ifs >> testcaseNum;
	for (int t = 0; t < testcaseNum; t++)
	{
		int N;
		ifs >> N;

		string *sides = new string[N];
		int *locations = new int[N];

		for (int n = 0; n < N; n++)
		{
			ifs >> sides[n] >> locations[n];
		}
		printf("Case #%d: %d\n", t + 1, solve(sides, locations, N));

		delete[] sides;
		delete[] locations;
	}

    return 0;
}
