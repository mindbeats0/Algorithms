
// SCC TOPSORT DAG
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50000;

int cost[MAXN+5];

vector<int>adj[MAXN+5],Tadj[MAXN+5];
bool vis[MAXN+5];
vector<int>topSort;
void dfs(int node){
	if(vis[node])return ;
	vis[node]=1;
	for(int i=0;i<adj[node].size();i++)dfs(adj[node][i]);
	topSort.push_back(node);
}

int comp,tot;
vector<int>nodes[MAXN+5];
int belong[MAXN+5],total[MAXN+5];

void dfs2(int node){
	if(vis[node])return ;
	vis[node]=1;

	belong[node]=comp;
	nodes[comp].push_back(node);
	tot+=cost[node];

	for(int i=0;i<Tadj[node].size();i++)dfs2(Tadj[node][i]);
}
int dp[MAXN+5];
int solve(int id){
	if(dp[id]!=-1)return dp[id];

	int ret=0;
	for(int i=0;i<nodes[id].size();i++){
		int u=nodes[id][i];
		for(int j=0;j<adj[u].size();j++){
			int v=adj[u][j];

			if(belong[u]!=belong[v])ret=max(ret,solve(belong[v]));
		}
	}
	return dp[id]=ret+total[id];
}
int main(){
	int T,N,M,u;
	scanf("%d",&T);
	for(int tt=1;tt<=T;tt++){
		scanf("%d",&N);

		for(int i=0;i<N;i++)
			adj[i].clear(),Tadj[i].clear();

		for(int i=0;i<N;i++){

			scanf("%d%d",&cost[i],&M);
			for(int j=0;j<M;j++){
				scanf("%d",&u);
				adj[i].push_back(u);
				Tadj[u].push_back(i);
			}
		}
		memset(vis,0,sizeof vis);
		topSort.clear();
		for(int i=0;i<N;i++)if(!vis[i])dfs(i);

		memset(vis,0,sizeof vis);
		comp=0;
		for(int i=topSort.size()-1;i>=0;i--){
			if(!vis[topSort[i]]){
				nodes[comp].clear();
				tot=0;
				dfs2(topSort[i]);
				total[comp]=tot;

				comp++;

			}
		}

		int res=0;
		memset(dp,-1,sizeof dp);
		for(int i=0;i<comp;i++)solve(i),res=max(res,dp[i]);
		printf("Case %d: %d\n",tt,res);
	}
	return 0;
}
