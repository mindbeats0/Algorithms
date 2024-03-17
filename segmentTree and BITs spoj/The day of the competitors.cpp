#include <bits/stdc++.h>
using namespace std;
const int MAXN =200000;
struct node{
    int c1,c2,c3;
    const bool operator <(const node&other)const{
        return c1<other.c1;
    }
}arr[MAXN];
int Tree[MAXN];
int lsb(int x){
    return x&(-x);
}
void update(int idx,int val){
    while(idx<MAXN){
        Tree[idx] = min(Tree[idx],val);
        idx += lsb(idx);
    }
}
int query(int idx){
    int ret = MAXN;
    while(idx){
        ret = min(ret,Tree[idx]);
        idx -= lsb(idx);
    }
    return ret;
}

int main(){
    int t,n;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d%d%d",&arr[i].c1,&arr[i].c2,&arr[i].c3);
        sort(arr,arr+n);
        for(int i=0;i<MAXN;i++)Tree[i]=MAXN;
        int res=0;
        for(int i=0;i<n;i++){
            if(query(arr[i].c2) > arr[i].c3)res++;
            update(arr[i].c2,arr[i].c3);
        }
        printf("%d\n",res);
    }
    return 0;
}
