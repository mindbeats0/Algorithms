// make a segment tree on ranges 0 to N-1
// each SegTree[v] holds: how many numbers from root to v in all ranges from 0 to N-1
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
int weight[MAXN+5];
int Tree[25*MAXN],L[25*MAXN],R[25*MAXN],node_counter,RootOfVertex[MAXN+5];

int head[MAXN+5],to[2*MAXN+5],nxt[2*MAXN+5],last;
int par[25][MAXN+5],depth[MAXN+5];

vector<int>topSort;

void addEdge(int f,int t){
    to[last]=t;
    nxt[last]=head[f];
    head[f]=last;
    last++;
}

void init(int idx, int s,int e,int val){
    if(s==e){
        Tree[idx] = s==val?1:0;
        return ;
    }
    L[idx]=node_counter++;
    R[idx]=node_counter++;
    init(L[idx],s,(s+e)/2,val);
    init(R[idx],(s+e)/2+1,e,val);
    Tree[idx] = Tree[L[idx]]+Tree[R[idx]];
}
void build(int idx_par,int idx, int s,int e,int val){
    if(s==e){
        Tree[idx] = Tree[idx_par]+1;
        return ;
    }
    int mid = (s+e)/2;
    if(val<=mid){
        L[idx]=node_counter++;
        build(L[idx_par],L[idx],s,mid,val);
        R[idx]=R[idx_par];
    }
    else{
        R[idx]=node_counter++;
        build(R[idx_par],R[idx],mid+1,e,val);
        L[idx]=L[idx_par];
    }

    Tree[idx] = Tree[L[idx]]+Tree[R[idx]];
}
bool vis[MAXN+5];
void dfs(int node){

    vis[node]=true;

    for(int edge=head[node];edge!=-1;edge=nxt[edge])if(!vis[to[edge]]){
        par[0][to[edge]]=node;
        depth[to[edge]] = depth[node]+1;
        dfs(to[edge]);
    }
    topSort.push_back(node);
}
int K;
int val_lca;
int query(int u,int v,int lca,int s,int e){

    if(s==e)return s;

    int mid=(s+e)/2;

    int lft = Tree[L[u]]+Tree[L[v]]-2*Tree[L[lca]]+ (val_lca>=s && val_lca<=mid );
    int rght = Tree[R[u]]+Tree[R[v]]-2*Tree[R[lca]]+ (val_lca>=mid+1 && val_lca<=e );


    if(lft>=K)return query(L[u],L[v],L[lca],s,mid);
    else {K-=lft; return query(R[u],R[v],R[lca],mid+1,e);}


}


int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];
	for(int i=0; i<20; i++) if( (diff>>i)&1 ) u = par[i][u];
	if(u == v) return u;

	for(int i=19; i>=0; i--) if(par[i][u] != par[i][v]) {
		u = par[i][u];
		v = par[i][v];
	}
	return par[0][u];
}

void build_parent(){

    for(int i=1; i<20; i++)
        for(int j=0; j<MAXN; j++)
            if(par[i-1][j] != -1)
                par[i][j] = par[i-1][par[i-1][j]];
}


int main(){
    int N,M,u,v,k;
    scanf("%d%d",&N,&M);

    vector<int>values;
    for(int i=0;i<N;i++)
        scanf("%d",&weight[i]),values.push_back(weight[i]);

    sort(values.begin(),values.end());
    values.resize(unique(values.begin(),values.end())-values.begin());

    for(int i=0;i<N;i++)
        weight[i]=lower_bound(values.begin(),values.end(),weight[i])-values.begin();


    memset(head,-1,sizeof head);
    for(int i=0;i<N-1;i++){
        scanf("%d%d",&u,&v);
        u--;v--;
        addEdge(u,v);
        addEdge(v,u);
    }

    memset(par,-1,sizeof par);
    dfs(0);

    memset(Tree,-1,sizeof Tree);
    memset(L,-1,sizeof L);
    memset(R,-1,sizeof R);
    init(node_counter++,0,N-1,weight[0]);



    for(int i=N-2;i>=0;i--){
        int node = topSort[i];
        RootOfVertex[node] = node_counter++;
        build(RootOfVertex[par[0][node]],RootOfVertex[node],0,N-1,weight[node]);

    }

    assert(node_counter<25*MAXN);

    build_parent();
    for(int i=0;i<M;i++){
        scanf("%d%d%d",&u,&v,&k);
        u--;v--;
        int lca = LCA(u,v);

        K=k;
        val_lca = weight[lca];
        int ans = query(RootOfVertex[u],RootOfVertex[v],RootOfVertex[lca],0,N-1);
        printf("%d\n",values[ans]);
    }
}
