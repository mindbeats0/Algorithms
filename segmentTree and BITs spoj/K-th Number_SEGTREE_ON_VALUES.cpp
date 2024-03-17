//SEG TREE is holding indices
// segtree ranges: values
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
int arr[MAXN+5];
map<int,int>mp;
int reall[MAXN+5],idxof[MAXN+5];
vector<int>Tree[4*MAXN];
void merge(vector<int>&ret,vector<int>&a,vector<int>&b){
    int i=0,j=0;
    while(i<a.size() && j<b.size()){
        if(a[i]<=b[j])ret.push_back(a[i++]);
        else ret.push_back(b[j++]);
    }
    while(i<a.size())ret.push_back(a[i++]);
    while(j<b.size())ret.push_back(b[j++]);
}
void build(int idx,int s,int e){
    if(s==e){
        Tree[idx].push_back(idxof[s]);
        return ;
    }
    int mid=(s+e)/2;
    build(idx*2,s,mid);
    build(idx*2+1,mid+1,e);
    merge(Tree[idx],Tree[idx*2],Tree[idx*2+1]);
}
int query(int idx,int s,int e,int x,int y,int k){

    if(s==e)return s;

    int left = upper_bound(Tree[idx*2].begin(),Tree[idx*2].end(),y) - lower_bound(Tree[idx*2].begin(),Tree[idx*2].end(),x);
    int right = upper_bound(Tree[idx*2+1].begin(),Tree[idx*2+1].end(),y) - lower_bound(Tree[idx*2+1].begin(),Tree[idx*2+1].end(),x);

    int mid=(s+e)/2;
    if(left<k){
        k-=left;
        return query(idx*2+1,mid+1,e,x,y,k);
    }
    else{
        return query(idx*2,s,mid,x,y,k);
    }

}
int main(){
    int n,m,x,y,k;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        mp[arr[i]];
    }
    int rnk=0;
    for(auto it=mp.begin();it!=mp.end();it++)
        it->second=rnk++;

    for(int i=0;i<n;i++){
        int old=arr[i];
        int neww=mp[arr[i]];
        reall[neww]=old;
        arr[i]=neww;
    }

    for(int i=0;i<n;i++)
        idxof[arr[i]]=i;

    build(1,0,n-1);
    while(m--){
        scanf("%d%d%d",&x,&y,&k);
        x--; y--;
        printf("%d\n",reall[query(1,0,n-1,x,y,k)]);
    }
}
