#include <bits/stdc++.h>
using namespace std;
const int MAXN = 40000;
pair<int,int>arr[MAXN+5];
vector<int>all;
int Lazy[8*MAXN];
void relax(int idx,int s, int e){

    if(s!=e){
        if(Lazy[idx]!=-1)Lazy[idx*2]=Lazy[idx*2+1]=Lazy[idx];
        Lazy[idx]=-1;
    }

}
void update(int idx,int qs,int qe,int s,int e,int col){
    relax(idx,s,e);
    if(s>qe || e<qs)return ;

    if(s>=qs && e<=qe){
        Lazy[idx]=col;
    }
    else{
        update(idx*2,qs,qe,s,(s+e)/2,col);
        update(idx*2+1,qs,qe,(s+e)/2+1,e,col);
    }
}
set<int>S;
void ask(int idx,int s, int e){

    relax(idx,s,e);
    if(s==e){if(Lazy[idx]!=-1)S.insert(Lazy[idx]);}
    else {
        ask(idx*2,s,(s+e)/2);
        ask(idx*2+1,(s+e)/2+1,e);
    }
}
int main(){
    int tc,n;
    scanf("%d",&tc);
    while(tc--){
        all.clear();
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%d%d",&arr[i].first,&arr[i].second);
            all.push_back(arr[i].first);
            all.push_back(arr[i].second);
        }
        sort(all.begin(),all.end());
        all.resize(unique(all.begin(),all.end())-all.begin());

        for(int i=0;i<n;i++){
            arr[i].first=lower_bound(all.begin(),all.end(),arr[i].first)-all.begin();
            arr[i].second=lower_bound(all.begin(),all.end(),arr[i].second)-all.begin();
        }

        memset(Lazy,-1,sizeof Lazy);
        for(int i=0;i<n;i++){
            update(1,arr[i].first,arr[i].second,0,all.size()-1,i);
        }


        S.clear();
        ask(1,0,all.size()-1);
        printf("%d\n",S.size());
    }
}
