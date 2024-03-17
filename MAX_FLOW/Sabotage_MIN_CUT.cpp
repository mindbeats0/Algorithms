#include<bits/stdtr1c++.h>
using namespace std;

#define MAXN 55
#define MAXE 1010

typedef long long ct; //ct capacity type

const ct oo = 1ll << 62;
int head[MAXN], headcpy[MAXN], from[MAXE],to[MAXE], nxt[MAXE];
ct cap[MAXE];
int last;
int n, src, snk;

inline void init() {
	memset(head, -1, n * sizeof(head[0]));
	last = 0;
}

inline void addEdge(int f, int t, ct cp) {
	nxt[last] = head[f];
	from[last]=f;
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
bool mark[MAXN];
void mark_set(int cur=src){
    mark[cur]=1;

    for (int i = head[cur]; i != -1; i = nxt[i]) {
        int t = to[i];
        if (!cap[i] || mark[t])
            continue;
        mark_set(t);
    }

}
int main() {
    int m;
    while(scanf("%d%d",&n,&m),n){
        src = 0;
        snk = 1;
        init();
        while (m--) {
            int a, b;
            ct c;
            scanf("%d%d%lld",&a,&b,&c);
            a--;
            b--;
            addAugEdge(a, b, c, c);
        }
       ct mf = dinic();

       memset(mark,0,sizeof mark);
       mark_set();

      // cout<<mf<<endl;
       for(int i=0;i<last;i++)
            if(!cap[i] && mark[from[i]] && !mark[to[i]] )
                printf("%d %d\n",from[i]+1,to[i]+1);
       printf("\n");

    }

	return 0;

}
