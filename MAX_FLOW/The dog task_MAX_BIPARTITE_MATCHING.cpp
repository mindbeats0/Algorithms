#include<bits/stdtr1c++.h>
using namespace std;

#define MAXN 210
#define MAXE (MAXN*MAXN*2)

typedef long long ct; //ct capacity type

const ct oo = 1ll << 62;
int head[MAXN], headcpy[MAXN], to[MAXE], from[MAXE], nxt[MAXE];
ct cap[MAXE],res[MAXN][MAXN];
int last;
int n, src, snk;

inline void init() {
	memset(head, -1, n * sizeof(head[0]));
	for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            res[i][j]=0;
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
    res[f][t] = c1;

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
pair<int,int>bob[105],dog[105];
#define x first
#define y second

double dist(pair<int,int>p1,pair<int,int>p2){
    double X = abs(p1.x-p2.x);
    double Y = abs(p1.y-p2.y);

    double dist2 = X*X + Y*Y;
    return sqrt(dist2);
}

int main() {

    int TC,N,M;
    scanf("%d",&TC);
    for(int tc=0;tc<TC;tc++){
        scanf("%d%d",&N,&M);
        for(int i=0;i<N;i++)
            scanf("%d%d",&bob[i].x,&bob[i].y);
        for(int i=0;i<M;i++)
            scanf("%d%d",&dog[i].x,&dog[i].y);


        n = N+M+1;
        src = N-1 + M;
        snk = N + M;
        init();

        for(int i=0;i<N-1;i++){
            for(int j=0;j<M;j++){

                if( 2*dist(bob[i],bob[i+1]) >= dist(bob[i],dog[j])+dist(dog[j],bob[i+1]))
                        addAugEdge(i, N-1+j, 1);

            }
        }

        for(int i=0;i<N-1;i++)addAugEdge(src,i, 1);
        for(int j=0;j<M;j++)addAugEdge(N-1+j,snk, 1);

        ct mf = dinic();
        printf("%lld\n",mf+N);

        int res[105];
        memset(res,-1,sizeof res);
        for(int i=0;i<last;i++){
            if(to[i]<N-1 && from[i]>=N-1 && from[i]<= N-1 + M-1 && cap[i] == 1 )
                res[to[i]] = from[i]-(N-1);
               // printf("here %d,%d\n",from[i]-(N-1),to[i]);
        }

        for(int i=0;i<N-1;i++){
            if(i)printf(" ");

            printf("%d %d",bob[i].x,bob[i].y);
            if(res[i]!=-1){
                int j = res[i];
                printf(" %d %d",dog[j].x,dog[j].y);
            }

        }
        printf(" %d %d\n",bob[N-1].x,bob[N-1].y);




        /*for(int i=0;i<N-1;i++){
            if(i)printf(" ");

            printf("%d %d",bob[i].x,bob[i].y);
            pair<int,int>place(-2000,-2000);
            for(int j=0;j<M;j++)
                if(res[N-1+j][i]==1)
                {place = dog[j]; break;}
            if(place.x!=-2000)printf(" %d %d",place.x,place.y);
        }
        printf(" %d %d\n",bob[N-1].x,bob[N-1].y);*/

        if(tc!=TC-1)printf("\n");
    }
    return 0;

}

