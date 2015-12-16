#include <stdio.h>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <omp.h>

using namespace std;

int main(void)
{

#pragma omp parallel for
	for(int n = 0; n < 10; n++) {
		printf("%d\n", n);
	}
}
