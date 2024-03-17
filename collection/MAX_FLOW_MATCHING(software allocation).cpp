#include<bits/stdtr1c++.h>
using namespace std;

#define MAXN 55
#define MAXE MAXN*MAXN

typedef long long ct; //ct capacity type

const ct oo = 1ll << 62;
int head[MAXN], headcpy[MAXN], to[MAXE], nxt[MAXE];
ct cap[MAXE];
ct res[MAXN][MAXN];
int last;
int n, src, snk;

inline void init() {
	memset(head, -1, n * sizeof(head[0]));
	memset(res, 0,  sizeof(res));
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

	res[f][t] = c1;
	res[f][t] = c2;

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

		res[cur][t] -= ret;
		res[t][cur] += ret;

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


char s[100];
int total_tasks;
void build(char *s){

    int task = s[0]-'A'+1;
    int cnt = s[1]-'0';
    total_tasks += cnt;

    addAugEdge(src, task , cnt);

    for(int i=3;i<strlen(s)-1;i++){
        int pc = s[i]-'0' + 27;
        addAugEdge(task, pc , 1);
    }
}
int main(){

  //  freopen("ib.in","r",stdin);


    while(gets(s)){


        n = 38;

        init();
        src = 0;
        snk = 37;

        for(int i=27;i<=36;i++)addAugEdge(i, snk , 1);

        total_tasks=0;
        build(s);

        while(gets(s)){
            if(strcmp(s,"") == 0)break;
            build(s);
        }



        if(dinic() == total_tasks){
            for(int pc=0;pc<10;pc++){
                char cc = '_';
                for(char task='A';task<='Z';task++){
                    if(res[pc+27][task-'A'+1]==1)
                        {cc = task; break;}
                }
                printf("%c",cc);
            }
            printf("\n");
        }
        else printf("!\n");
    }
    return 0;
}

