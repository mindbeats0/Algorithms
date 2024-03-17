#include <bits/stdc++.h>
using namespace std;
const int MAXN=100000;
int arr[MAXN+5];
map<int,int>mp;
int old[MAXN+5];

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

    int mid = (s+e)/2;
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
    if(s==e)return s;

    int left = p2->left->count - p1->left->count;
    int right = p2->right->count - p1->right->count;

    int mid = (s+e)/2;
    if(k>left)
        return query(p1->right,p2->right,mid+1,e,k-left);
    else
        return query(p1->left,p2->left,s,mid,k);
}
int main(){
    int n,m,x,y,k;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        mp[arr[i]];
    }
    int maxi=1;
    for(auto it=mp.begin();it!=mp.end();it++)
        it->second=maxi++; 
    for(int i=1;i<=n;i++){
        int neww=mp[arr[i]];
        int oldd=arr[i];
        arr[i]=neww;
        old[neww]=oldd;
    }
    init(root[0],1,maxi);
    for(int i=1;i<=n;i++){
        // root[i] : from 1 to i
        build(root[i-1],root[i],1,maxi,arr[i]);
    }
    while(m--){
        scanf("%d%d%d",&x,&y,&k);
        printf("%d\n",old[query(root[x-1],root[y],1,maxi,k)]);
    }
}
