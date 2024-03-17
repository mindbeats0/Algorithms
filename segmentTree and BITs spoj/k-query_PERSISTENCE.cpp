#include <bits/stdc++.h>
using namespace std;
const int MAXN=3e4;
const int MAXM=2e5;
int arr[MAXN+5];
map<int,int>mp;

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
void build(node*prv,node*&cur,int s,int e,int val){
    cur = new node(prv->count+1,NULL,NULL);

    if(s==e)return;

    int mid = (s+e)>>1;
    if(val>mid){
        cur->left = prv->left;
        build(prv->right,cur->right,mid+1,e,val);
    }
    else{
        cur->right = prv->right;
        build(prv->left,cur->left,s,mid,val);
    }
}
int query(node*p1,node*p2,int s,int e,int k){
    if(e<=k)return 0;
    
    if(s>k)return p2->count- p1->count;
     
     int mid=(s+e)>>1;
    return query(p1->left,p2->left,s,mid,k) + query(p1->right,p2->right,mid+1,e,k);
    
}
int st[MAXM+5],en[MAXM+5],kk[MAXM+5];
int main(){
    int n,m,x,y,k;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        mp[arr[i]];
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&st[i],&en[i],&kk[i]);
        mp[kk[i]];
    }
    
    int maxi=1;
    for(auto it=mp.begin();it!=mp.end();it++)
        it->second=maxi++; 
        
    for(int i=1;i<=n;i++)
        arr[i]=mp[arr[i]];
    
        
    init(root[0],1,maxi);
    
    for(int i=1;i<=n;i++){
        // root[i] : from 1 to i
        build(root[i-1],root[i],1,maxi,arr[i]);
    }
    
    for(int i=1;i<=m;i++){
        x=st[i],y=en[i],k=mp[kk[i]];
        printf("%d\n",query(root[x-1],root[y],1,maxi,k));
    }
}
