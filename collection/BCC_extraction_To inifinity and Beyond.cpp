// BCC extraction to infinity and beyond
#include <bits/stdc++.h>
using namespace std;
const int MAXN=300;
const int MAXE=MAXN*MAXN;
int head[MAXN+5],to[MAXE+5],nxt[MAXE+5],last;
void addEdge(int f,int t){
	to[last]=t;
	nxt[last]=head[f];
	head[f]=last;
	last++;
}

int dfs_num[MAXN+5],dfs_low[MAXN+5],dfs_counter,parent[MAXN+5],root;
int BCC;
int en[MAXN+5],req[MAXN+5];
int N,E,B;
bool taken[MAXN+5];
vector<int>bcc[MAXN+5];
vector<int>supply;

void extract(int u,int v,stack<pair< int,int> >&S){

	 int tu=-1,tv=-1;
	 while(tu!=u && tv!=v){
		 tu=S.top().first,tv=S.top().second,S.pop();
		 bcc[BCC].push_back(tu);
		 bcc[BCC].push_back(tv);
	 }
	 if(bcc[BCC].size()==2)bcc[BCC].clear();
	 else {
		sort(bcc[BCC].begin(),bcc[BCC].end());
		bcc[BCC].resize(unique(bcc[BCC].begin(),bcc[BCC].end())-bcc[BCC].begin());
		for(int i=0;i<bcc[BCC].size();i++)taken[bcc[BCC][i]]=1;
		BCC++;
	}

}
void solve(int u,stack<pair<int,int> >&S){
	dfs_num[u] = dfs_low[u] = dfs_counter++;
	for(int edge=head[u];edge!=-1;edge=nxt[edge])if(to[edge]!=parent[u]){
		int v =to[edge];
		if(dfs_num[v]==-1){
			parent[v]=u;
			S.push(make_pair(u,v));
			solve(v,S);
			dfs_low[u] = min(dfs_low[u],dfs_low[v]);


			if( dfs_low[v]>=dfs_num[u]){
				extract(u,v,S);
			}


		}
		else // back edge
			dfs_low[u]  = min(dfs_low[u], dfs_num[v]);

	}
}

bool ok(int limit){
	int i=0,j=0;
	// regions buzz
	while(i<BCC && j<B){
		if(abs(supply[i]-req[j])<=limit)i++,j++;
		else j++;
	}
	return i==BCC;
}

int main(){
	int T,u,v;
	scanf("%d",&T);
	for(int tt=1;tt<=T;tt++){
		scanf("%d%d%d",&N,&E,&B);
		for(int i=0;i<N;i++)scanf("%d",&en[i]);
		for(int i=0;i<B;i++)scanf("%d",&req[i]);

		memset(head,-1,sizeof head);
		for(int i=0;i<MAXN;i++)bcc[i].clear();
		last=0;
		for(int i=0;i<E;i++){
			scanf("%d%d",&u,&v);
			u--; v--;
			addEdge(u,v);
			addEdge(v,u);
		}


		memset(parent,-1,sizeof parent);
		memset(dfs_num,-1,sizeof dfs_num);
		dfs_counter=0;

		stack<pair<int,int> >S;
		BCC=0;
		memset(taken,0,sizeof taken);
		for(int i=0;i<N;i++)if(dfs_num[i]==-1)
			solve(i,S);



	  for(int i=0;i<N;i++)if(!taken[i])bcc[BCC++].push_back(i);



	  supply.clear();
	  for(int i=0;i<BCC;i++){
		  int tot=0;
		  for(int j=0;j<bcc[i].size();j++)
			   tot+=en[bcc[i][j]];


		  supply.push_back(tot);
	 }

		if(B<BCC)printf("Buzz Mission %d: %d No\n",tt,BCC);


		else{
		    sort(supply.begin(),supply.end());
			sort(req,req+B);
			int lo=0,hi=1e6,mid,ans=-1;
			while(lo<=hi){
				mid=(lo+hi)/2;
				if(ok(mid))ans=mid,hi=mid-1;
				else lo=mid+1;
			}
			assert(ans!=-1);
			printf("Buzz Mission %d: %d %d\n",tt,supply.size(),ans);

		}

	}
	return 0;
}
