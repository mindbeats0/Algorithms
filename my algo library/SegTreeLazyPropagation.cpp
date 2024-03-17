/*
 * Segment Tree.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: Osama Hatem
 */

#include <bits/stdtr1c++.h>
#include <ext/numeric>

using namespace std;

const int MAXN = 1e5 + 5;

int arr[MAXN], tree[4 * MAXN], lazy[4 * MAXN];

void build(int n, int s, int e) {
	if (s == e) {
		tree[n] = arr[s];
		return;
	}
	int mid = (s + e) / 2;
	build(n * 2, s, mid);
	build(n * 2 + 1, mid + 1, e);
	tree[n] = tree[n * 2] + tree[n * 2 + 1];
}
void relax(int n, int s, int e) {
	tree[n] += (e - s + 1) * lazy[n];
	if (s != e) {
		lazy[n * 2] += lazy[n];
		lazy[n * 2 + 1] += lazy[n];
	}
	lazy[n] = 0;
}
int query(int qs, int qe, int n, int s, int e) {
	relax(n, s, e);
	if (s > qe || e < qs || qe < qs)
		return 0;
	if (s >= qs && e <= qe)
		return tree[n];
	int mid = (s + e) / 2;
	return query(qs, qe, n * 2, s, mid)
			+ query(qs, qe, n * 2 + 1, mid + 1, e);
}

void update(int qs, int qe, int val, int n, int s, int e) {
	relax(n, s, e);

	if (s > qe || e < qs || qe < qs)
		return;
	if (s >= qs && e <= qe) {
		lazy[n] += val;
		relax(n, s, e);
		return;
	}
	int mid = (s + e) / 2;
	update(qs, qe, val, n * 2, s, mid);
	update(qs, qe, val, n * 2 + 1, mid + 1, e);
	tree[n] = tree[n * 2] + tree[n * 2 + 1];
}

int main() {
	return 0;
}
