

/*
	By Anudeep Nekkanti
	Editorial at http://blog.anudeep2011.com/mos-algorithm/
	Question at http://www.spoj.com/problems/DQUERY/
	O( (N+M) * sqrt N )
*/

#include <cstdio>
#include <algorithm>
using namespace std;

#define N 311111
#define A 1111111
#define BLOCK 555 // ~sqrt(N)

int cnt[A], a[N], ans[N], answer = 0;

struct node {
	int L, R, i;
}q[N];

bool cmp(node x, node y) {
	if(x.L/BLOCK != y.L/BLOCK) {
		// different blocks, so sort by block.
		return x.L/BLOCK < y.L/BLOCK;
	}
	// same block, so sort by R value
	return x.R < y.R;
}

void add(int idx) {
	cnt[a[idx]]++;
	if(cnt[a[idx]] == 1) {
		answer++;
	}
}

void remove(int idx) {
	cnt[a[idx]]--;
	if(cnt[a[idx]] == 0) {
		answer--;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);

	int m;
	scanf("%d", &m);
	for(int i=0; i<m; i++) {
		scanf("%d%d", &q[i].L, &q[i].R);
		q[i].L--; q[i].R--;
		q[i].i = i;
	}

	sort(q, q + m, cmp);

	int currentL = 0, currentR = 0;
	// i have numbers from : currentL to currentR-1
	for(int i=0; i<m; i++) {
		int L = q[i].L, R = q[i].R;
		while(currentL < L) {
			remove(currentL);
			currentL++;
		}
		while(currentL > L) {
			currentL--;
			add(currentL);
		}
		while(currentR <= R) {
			add(currentR);
			currentR++;
		}
		while(currentR-1 > R) {
			currentR--;
			remove(currentR);
			
		}
		ans[q[i].i] = answer;
	}

	for(int i=0; i<m; i++)
		printf("%d\n", ans[i]);
}
