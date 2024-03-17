#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 1e5;
const int INF = 1e6;
vector<int>adj[MAXN+5];
int bad[MAXN+5],dist_down[MAXN+5],dist_up[MAXN+5],max1[MAXN+5],max2[MAXN+5],d;
int dfs1(int node,int par){
	int mx1=-INF,mx2=-INF,ret=-INF;
	if(bad[node])ret=0;
	for(int i=0;i<(int)adj[node].size();i++)if(adj[node][i]!=par){

		int now = dfs1(adj[node][i],node);
		ret=max(ret,now);

		if(now>mx1){mx2=mx1; mx1=now;}
		else if(now>mx2)mx2=now;

	}
	max1[node]=mx1;
	max2[node]=mx2;

    dist_down[node]=ret;
	return ret+1;
}

void dfs2(int node,int par){


    int sibling;
    if(max1[par]==dist_down[node]+1)sibling=max2[par];
    else sibling=max1[par];


    dist_up[node] = max(dist_up[par]+1,sibling+1);

    if(bad[node])dist_up[node] = max(0,dist_up[node]);


	for(int i=0;i<(int)adj[node].size();i++)if(adj[node][i]!=par)
		dfs2(adj[node][i],node);

}
int main(){
	int n,m,x,y;
	scanf("%d%d%d",&n,&m,&d);
	for(int i=0;i<m;i++){
		scanf("%d",&x);
		bad[x]=1;
	}
	for(int i=0;i<n-1;i++){
		scanf("%d%d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dist_down[0]=max1[0]=max2[0]=dist_up[0]=-INF;
	dfs1(1,0);
	dfs2(1,0);

	int res=0;
	for(int i=1;i<=n;i++){if(dist_down[i]<=d && dist_up[i]<=d )res++;
	}
	printf("%d\n",res);
}
