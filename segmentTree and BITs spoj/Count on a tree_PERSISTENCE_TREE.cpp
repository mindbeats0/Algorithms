/*
http://blog.anudeep2011.com/persistent-segment-trees-explained-with-spoj-problems/
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
const int MAXL = 18;
int head[MAXN+5],to[2*MAXN+5],nxt[2*MAXN+5],last;
void addEdge(int f,int t){
    to[last]=t;
    nxt[last]=head[f];
    head[f]=last;
    last++;
}
int weight[MAXN+5],old[MAXN+5],par[MAXL+5][MAXN+5],depth[MAXN+5];
int q[MAXN+5],ptr;
void dfs(int node){
    q[ptr++]=node;
    depth[node] = depth[par[0][node]]+1;
    for(int edge=head[node];edge!=-1;edge=nxt[edge])if(par[0][node] != to[edge]){
        par[0][to[edge]] = node;
        dfs(to[edge]);
    }
}


struct node{
    int count;
    node*left,*right;
    node(){}
    node(int count,node*left,node*right):count(count),left(left),right(right){}
};
node*root[MAXN+5];
void init(node*&p,int s,int e){
    p = new node(0,NULL,NULL);
    if(s==e)return ;
    int mid = (s+e)/2;
    init(p->left,s,mid);
    init(p->right,mid+1,e);
}
void build(node*parent,node*&cur,int s,int e,int val){
    cur = new node(parent->count+1,NULL,NULL);
    if(s==e)return ;

    int mid=(s+e)/2;

    if(val>mid){
        cur->left = parent->left;
        build(parent->right,cur->right,mid+1,e,val);
    }
    else{
        cur->right = parent->right;
        build(parent->left,cur->left,s,mid,val);
    }
}
void init_ancestors(int n){
    for(int i=1;i<MAXL;i++){
        for(int j=1;j<=n;j++){
            if(par[i-1][j]!=-1)
                par[i][j] = par[i-1][par[i-1][j]];
        }
    }
}
int LCA(int u,int v){
    if(depth[u]<depth[v])swap(u,v);
    int diff=depth[u]-depth[v];
    for(int i=0;i<MAXL;i++)if((diff>>i)&1)u=par[i][u];
    if(u==v)return u;

    assert(depth[u]==depth[v]);

    for(int i=MAXL-1;i>=0;i--){
        if(par[i][u]!=par[i][v])
            u=par[i][u],v=par[i][v];
    }
    assert(u>1);
    return par[0][u];
}
int query(node*u,node*v,node*lca,node*par_lca,int s,int e,int k){
    if(s==e)return s;

    int left = u->left->count + v->left->count - lca->left->count - par_lca->left->count;
    int right = u->right->count + v->right->count - lca->right->count - par_lca->right->count;

    int mid=(s+e)/2;
    if(left<k)return query(u->right,v->right,lca->right,par_lca->right,mid+1,e,k-left);
    return query(u->left,v->left,lca->left,par_lca->left,s,mid,k);

}
int main(){
    int n,m,u,v,k;
    scanf("%d%d",&n,&m);
    map<int,int>mp;
    for(int i=1;i<=n;i++){
        scanf("%d",&weight[i]);
        mp[weight[i]];
    }



   // rank weights;
    int maxi=0;
    map<int,int>::iterator it;
    for(it=mp.begin();it!=mp.end();it++)
        it->second = maxi++;
    for(int i=1;i<=n;i++){
        int oldd = weight[i];
        int neww = mp[weight[i]];
        weight[i]=neww; old[neww]=oldd;
    }

    memset(head,-1,sizeof head);
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    memset(par,-1,sizeof par);
    par[0][1]=0;
    dfs(1);
    init_ancestors(n);
    init(root[0],0,maxi-1);

    for(int i=0;i<n;i++){
        int node=q[i];
        build(root[par[0][node]],root[node],0,maxi-1,weight[node]);
    }
    while(m--){

        scanf("%d%d%d",&u,&v,&k);
        int lca = LCA(u,v);
        int ans = query(root[u],root[v],root[lca],root[par[0][lca]],0,maxi-1,k);

        printf("%d\n",old[ans]);
    }
    return 0;
}
