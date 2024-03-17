#include <bits/stdc++.h>
using namespace std;
const int MAXV = 105;
#define INF ((int)1e6)
int res[MAXV][MAXV];
queue<int>q;
vector<int>dist,p; 
int n,s,t;
int augment(int curNode,int mincap){

	if(curNode == s)return mincap;
	
	int ret = augment(p[curNode],min(mincap,res[p[curNode]][curNode]));
	res[p[curNode]][curNode] -= ret;
	res[curNode][p[curNode]] += ret;
	return ret;
}

bool BFS(){
    
    while(!q.empty())q.pop();		
	dist.assign (MAXV,INF); 
	p.assign (MAXV,-1);
	
	q.push(s); dist[s]=0;
	while(!q.empty()){
		int cur = q.front(); q.pop();
		
		if(cur == t)return true;
		
		for(int i=0;i<n;i++)
			if(dist[i] == INF && res[cur][i]>0)
				dist[i] = dist[cur]+1,p[i] = cur,q.push(i);
	}
	return false;
}

int MAXFLOW(){
	
	int ret=0;
	while(BFS()){ // while there's an s-t path
		int flow = augment(t,INF);
		ret += flow;		
	}
	return ret;
}

int main(){
	int c,u,v,w,tc=0;
	while(scanf("%d",&n),n){
		tc++;
		memset(res,0,sizeof res);
		scanf("%d%d%d",&s,&t,&c);
		s--; t--;
		for(int i=0;i<c;i++){
			scanf("%d%d%d",&u,&v,&w);
			u--; v--;
			res[u][v] += w;
			res[v][u] += w;
		}
		
		int res = MAXFLOW();
		
		printf("Network %d\n",tc);
		printf("The bandwidth is %d.\n\n",res);
		
	}
	return 0;
}
