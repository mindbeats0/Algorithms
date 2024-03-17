
#include<bits/stdtr1c++.h>
using namespace std;

#define MAXN 510
#define MAXE (MAXN*MAXN*2)

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
int h[505];
char gender[505];
char buff1[105],buff2[105];
string music[505],sport[505];
int main() {

    int tc,m;
    scanf("%d",&tc);
    while(tc--){

        scanf("%d",&m);
        n = m + 2;
        src = 0;
        snk = m + 1;
        init();
        for(int i=1;i<=m;i++) {
                //35 M classicism programming
            scanf("%d%*c%c%s%s",&h[i],&gender[i],buff1,buff2);
            music[i]=buff1,sport[i]=buff2;

            if(gender[i]=='M')addAugEdge(src, i, 1);
            else addAugEdge(i, snk, 1);
        }

        for(int i=1;i<=m;i++) {
            for(int j=1;j<=m;j++) {
                //height gender music sport
                if(gender[i]=='M' && gender[j]=='F' && abs(h[i]-h[j])<=40 && music[i]==music[j] &&sport[i]!=sport[j]){
                    addAugEdge(i, j, 1);
                    //printf("%d,%d ****** (%c),(%c)\n",i,j,gender[i],gender[j]);
                }

            }
        }
        printf("%lld\n",m-dinic());

    }
	return 0;
}
