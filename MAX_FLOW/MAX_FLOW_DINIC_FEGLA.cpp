#include<bits/stdtr1c++.h>
using namespace std;

#define MAXN 5002
#define MAXE 30004*2

typedef long long ct; //ct capacity type

const ct oo = 1ll << 62;
int head[MAXN], headcpy[MAXN], to[MAXE], nxt[MAXE];
ct cap[MAXE];
int last;
int n, src, snk;

inline void init() {
	memset(head, -1, n * sizeof(head[0]));
	last = 0;
}

inline void addEdge(int f, int t, ct cp) {
	nxt[last] = head[f];
	to[last] = t;
	cap[last] = cp;
	head[f] = last++;
}

inline void addAugEdge(int f, int t, ct c1, ct c2 = 0) {
	addEdge(f, t, c1);
	addEdge(t, f, c2);

}
int rnk[MAXN];
ct ddfs(int cur = src, ct minic = oo) {
	if (cur == snk)
		return minic;

	for (int &i = headcpy[cur]; i != -1; i = nxt[i]) {
		int t = to[i];
		if (!cap[i] || rnk[t] != rnk[cur] + 1)
			continue;

		ct ret = ddfs(t, min(minic, cap[i]));
		cap[i] -= ret;
		cap[i ^ 1] += ret;
		if (ret)
			return ret;
	}
	return 0;

}
int Q[MAXN];
int ID = 1;
int vis[MAXN];
bool dbfs() {
	ID++;
	int Qi = 0;
	Q[Qi++] = src;
	vis[src] = ID;
	rnk[src] = 0;

	for (int in = 0; in < Qi; in++) {
		int cur = Q[in];
		int r = rnk[cur];
		for (int i = head[cur]; i != -1; i = nxt[i]) {
			int t = to[i];
			if (!cap[i] || vis[t] == ID)
				continue;
			vis[t] = ID;
			rnk[t] = r + 1;
			if (t == snk)
				return 1;
			Q[Qi++] = t;
		}
	}

	return 0;

}
ct dinic() {
	if (src == snk)
		return oo;
	ct ret = 0;
	while (dbfs()) {
		ct f;
		memcpy(headcpy, head, n * sizeof(head[0]));
		while (f = ddfs(), f)
			ret += f;
	}
	return ret;
}
int main() {
/*#ifndef ONLINE_JUDGE
	freopen("2.in", "r", stdin);

#endif // ONLINE_JUDGE*/
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int m;

	cin >> n >> m;

    // initialize n if not scanned
	src = 0;
	snk = n - 1;
	init();
	while (m--) {
		int a, b;
		ct c;
		cin >> a >> b >> c;
		a--;
		b--;
		addAugEdge(a, b, c, c);
	}
	cout << dinic() << "\n";

	return 0;

}
