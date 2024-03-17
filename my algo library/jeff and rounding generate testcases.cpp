#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <string.h>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
typedef long long ll;
double dp[400][200];
double a[200];
int INT[200];
int F[200];
double solveDP(int n, double *a){
	for (int i = 0; i<400; i++)for (int j = 0; j<200; j++)dp[i][j] = 1e4;
	dp[2 * n][n] = 0;

	for (int i = 2 * n - 1; i >= 0; i--){

		for (int f = 0; f <= n; f++){

			// take ceil
			dp[i][f] = dp[i + 1][f] + (a[i] - ceil(a[i]));

			// take floor
			if (f<n && abs(dp[i][f])> abs(dp[i + 1][f + 1] + (a[i] - floor(a[i]))))
				dp[i][f] = dp[i + 1][f + 1] + (a[i] - floor(a[i]));

		}

	}
	return abs(dp[0][0]);
}
double solveGreedy(int n,int *INT,int *F){
	int sum=0, zero=0;
	n *= 2;
	for (int i = 0; i<n; ++i){
		sum += F[i];
		zero += !F[i];
	}
	n /= 2;
	int res = 1 << 29;
	for (int i = 0; i <= n; ++i)
	if (i + zero >= n && n * 2 - zero >= i)
		res = min(res, abs(i * 1000 - sum));
	return res / 1000.0;
}
int main()
{
	srand(time(0));
	int cases=1;
	while (true){
		//printf("\r                   \r%d", cases++);
		int n = rand() % 50 + 1;
		for(int i=0;i<n*2;++i){
			int num=rand()%100000;
			if(rand()%3==0)
				num=0;
			INT[i] = num / 1000;
			F[i] = num % 1000;
			a[i] = INT[i] + F[i] / 1000.0;
		}
		if(abs(solveDP(n,a)-solveGreedy(n,INT,F))>1e-9){
			printf("%.9lf\t%.9lf\n", solveDP(n, a), solveGreedy(n, INT, F));
			printf("%d\n", n);
			for (int i = 0; i<2 * n; ++i)
				printf("%.3lf ", a[i]);
			puts("");
			return 0;
		}
	}
	return 0;
}
