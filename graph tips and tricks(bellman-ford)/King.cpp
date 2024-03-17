#include <bits/stdc++.h>
using namespace std;
const int MAXN=100;
const int MAXE=200;
int head[MAXN+5],to[MAXE+5],cost[MAXE+5],nxt[MAXE+5],last;
int dist[MAXN+5];
void addEdge(int f,int t,int c){
    to[last]=t;
    cost[last]=c;
    nxt[last]=head[f];
    head[f]=last;
    last++;
}
int main(){
    int n,m,a,b,k;
    char op[5];
    while(scanf("%d%d",&n,&m),n){
        memset(head,-1,sizeof head);
        last=0;
        for(int i=0;i<m;i++){
            scanf("%d%d%s%d",&a,&b,op,&k);
            b=a+b;
            if(op[0]=='g'){
                k++;
                addEdge(b,a-1,-k);
            }
            else{
                k--;
                addEdge(a-1,b,k);
            }
        }


        //there are n+1 node : from 0 to n
        // make dummy node n+1
        int src=n+1;

        dist[src]=0;
        for(int i=0;i<=n;i++){
            addEdge(src,i,0);
            dist[i]=1<<30;
        }


        for(int i=0;i<n+1;i++){ // there n+2 node, loop n+1 times
            for(int f=0;f<=n+1;f++){
                for(int edge=head[f];edge!=-1;edge=nxt[edge]){
                    int t=to[edge];
                    dist[t] = min(dist[t],dist[f]+cost[edge]);
                }
            }
        }
        bool neg_cycles=0;
        for(int f=0;f<=n+1;f++){
            for(int edge=head[f];edge!=-1;edge=nxt[edge]){
                int t=to[edge];
                if(dist[f]+cost[edge]<dist[t]){
                    neg_cycles=true;
                    break;
                }
            }
            if(neg_cycles)break;
        }
        if(neg_cycles)printf("successful conspiracy\n");
        else printf("lamentable kingdom\n");
    }
    return 0;
}
