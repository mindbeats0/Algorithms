#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5;
int head[MAXN+5],to[2*MAXN+5],nxt[2*MAXN+5],last;
vector<pair<int,int> >res;
void  addEdge(int f,int t){
    to[last]=t;
    nxt[last]=head[f];
    head[f]=last;
    last++;
}
int dfs_counter,dfs_num[MAXN+5],dfs_low[MAXN+5],parent[MAXN+5];
int root,rootChildren[MAXN+5];
void init(){
    dfs_counter=0;
    memset(dfs_num,-1,sizeof(dfs_num));
    memset(rootChildren,0,sizeof(rootChildren));
}

int ArticulationAndBridges(int node){
    dfs_low[node] = dfs_num[node] = dfs_counter++;

    for(int edge=head[node];edge!=-1;edge=nxt[edge]){

        int u=node,v=to[edge];
        if(v==parent[u])continue;

        if(dfs_num[v]==-1){ // go and flood the rest of tree
            parent[v]=u;
            if(u==root)rootChildren[root]++;
            ArticulationAndBridges(v);
            dfs_low[u] = min(dfs_low[u],dfs_low[v]);

            /*
            if(dfs_low[v]>=dfs_num[u]) // u is articulation point
            */
            if(dfs_low[v]>dfs_num[u])  // u-v is bridge
                res.push_back(make_pair(min(u,v),max(u,v)));
        }
        else if(v!=parent[u]){ // back edge
            dfs_low[u] = min(dfs_low[u],dfs_low[v]);
        }

    }
}
int main(){
    int N,k,u,v;
    while(scanf("%d",&N)!=EOF){
        memset(head,-1,sizeof head);
        last=0;
        for(int i=0;i<N;i++){
           // 0 (1) 1
            scanf("%d",&u);
            scanf("%*c%*c%d%*c%*c",&k);
            for(int j=0;j<k;j++){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        res.clear();
        init();
        for(int i=0;i<N;i++)
            if(dfs_num[i]==-1)
                root=i,ArticulationAndBridges(i);

        sort(res.begin(),res.end());
        printf("%d critical links\n",res.size());
        for(int i=0;i<res.size();i++)printf("%d - %d\n",res[i].first,res[i].second);
        printf("\n");
    }
}
