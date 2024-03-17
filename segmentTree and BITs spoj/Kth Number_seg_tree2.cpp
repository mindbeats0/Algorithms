#include <bits/stdc++.h>
using namespace std;
const int MAXN=100000;
int arr[MAXN+5];
int cnt=0;
int root[MAXN+5];
int Tree[25*MAXN],L[25*MAXN],R[25*MAXN];
vector<int>all;
void build(int idx,int s, int e){
    Tree[idx]=0;
    if(s==e)return ;
    L[idx]=cnt++;
    R[idx]=cnt++;
    build(L[idx],s,(s+e)/2);
    build(R[idx],(s+e)/2+1,e);

}
void update(int prv,int idx,int s, int e,int val){
    Tree[idx]=Tree[prv]+1;


    if(s==e)return ;
    int mid = (s+e)/2;
    if(val<=mid){//create new left
        L[idx]=cnt++;
        R[idx]=R[prv];
        update(L[prv],L[idx],s,mid,val);
    }
    else {//create new right
        R[idx]=cnt++;
        L[idx]=L[prv];
        update(R[prv],R[idx],mid+1,e,val);
    }

}
int query(int prv,int idx,int s,int e,int k){
   // cout<<s<<","<<e<<"   "<<k<<endl;
    if(s==e)return s;
    int lft =  Tree[L[idx]]-Tree[L[prv]];
    int rght = Tree[R[idx]]-Tree[R[prv]];

    if(lft<k){
        k-=lft;
        return query(R[prv],R[idx],(s+e)/2+1,e,k);
    }
    else{
        return query(L[prv],L[idx],s,(s+e)/2,k);
    }

}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        all.push_back(arr[i]);
    }
    sort(all.begin(),all.end());
    all.resize(unique(all.begin(),all.end())-all.begin());


    memset(Tree,-1,sizeof Tree);
    memset(L,-1,sizeof L);
    memset(R,-1,sizeof R);
    root[0]=cnt++;
    build(root[0],0,n-1);
    for(int i=1;i<=n;i++){
        root[i]=cnt++;
        update(root[i-1],root[i],0,n-1,lower_bound(all.begin(),all.end(),arr[i])-all.begin());
    }


    int i,j,k;
    for(int q=0;q<m;q++){
        scanf("%d%d%d",&i,&j,&k);
        int ans = query(root[i-1],root[j],0,n-1,k);
        printf("%d\n",all[ans]);
    }

}
