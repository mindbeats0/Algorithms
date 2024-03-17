#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1030;
pair<int,int>input[N*N+5];
ll Tree[N+5];
 
int lsb(int x){
    return x&(-x);
}
void update(int idx,int val){
    while(idx<N){
        Tree[idx] += val;
        idx += lsb(idx);
    }
}
ll query(int idx){
    ll ret=0;
    while(idx){
        ret += Tree[idx];
        idx -= lsb(idx);
    }
    return ret;
}
 
int main(){
    int T,n,m,k,y;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        scanf("%d%d%d",&n,&m,&k);
        ll res=0;
        memset(Tree,0,sizeof Tree);
        for(int i=0;i<k;i++)
           scanf("%d%d",&input[i].first,&input[i].second);
 
        sort(input,input+k);
 
        for(int i=0;i<k;i++){
           y=input[i].second;
           res += query(m) - query(y);
           update(y,1);
        }
        printf("Test case %d: %lld\n",t,res);
    }
}
