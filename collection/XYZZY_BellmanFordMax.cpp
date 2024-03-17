// XYZZY BELLMAND FORD MAX
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100;
const int MAXE=10000;
#define INF 1e6
int head[MAXN+5],to[MAXE+5],nxt[MAXE+5],last,en[MAXN+5],dist[MAXN+5];
void addEdge(int f,int t){
    to[last]=t;
    nxt[last]=head[f];
    head[f]=last;
    last++;
}
int comp,vis[MAXN+5];
bool dfs(int node,int n){
    if(vis[node]==comp)return false;
    vis[node]=comp;

    if(node==n-1)return true;
    for(int edge=head[node];edge!=-1;edge=nxt[edge]){
        if(dfs(to[edge],n))return true;
    }
    return false;
}
int main(){


    int n,k,x;
    while(scanf("%d",&n),n!=-1){
        memset(head,-1,sizeof head);
        last=0;
        for(int i=0;i<n;i++){
            scanf("%d%d",&en[i],&k);
            for(int j=0;j<k;j++){
                scanf("%d",&x);
                addEdge(i,x-1);
            }
        }


        dist[0]=100;
        for(int i=1;i<n;i++)dist[i]=-INF;


        for(int it=0;it<n-1;it++){
            for(int f=0;f<n;f++){
                if(dist[f]<=0)continue;

                for(int edge=head[f];edge!=-1;edge=nxt[edge]){
                    int t=to[edge];
                    dist[t] = max(dist[t],dist[f]+en[t]);
                }
            }

        }
        if(dist[n-1]>0){
            printf("winnable\n");
            continue;
        }

        bool ans=0;
        for(int f=0;f<n;f++){
            if(dist[f]<=0)continue;
            for(int edge=head[f];edge!=-1;edge=nxt[edge]){
                int t=to[edge];
                if(dist[t]<dist[f]+en[t] && (comp++,dfs(t,n)) ){
                     printf("winnable\n");
                     ans=1;
                     break;
                }
            }
            if(ans)break;
        }
        if(ans)continue;
        printf("hopeless\n");
    }
    return 0;
}
