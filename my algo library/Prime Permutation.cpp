#include <bits/stdc++.h>
using namespace std;
#define sz(a)  ((int)(a).size())
const int N=1000;
const int inf=5000;
int par[N+5],h[N+5],sz[N+5];
char letter_in_set[N+5];
void init(){
    for(int i=0;i<=N;i++)h[i]=1,sz[i]=1,par[i]=i;
}
int find(int e){
    if(par[e]==e)return e;
    return par[e]=find(par[e]);

}
void join(int e1,int e2){
    e1=find(e1);
    e2=find(e2);

    if(e1!=e2){
        if(h[e1]<h[e2])swap(e1,e2);
        par[e2]=e1;
        if(h[e1]==h[e2])h[e1]++;
        sz[e1]+=sz[e2];
    }

}

bool iscomposite[N+5];
int occ[200];
int main(){
    string S;
    cin>>S;

    for(int i=0;i<sz(S);i++)occ[S[i]]++;

    init();
    for(int i=2;i<=sz(S);i++){
        if(iscomposite[i])continue;
        for(int j=i+i;j<=sz(S);j+=i){
           iscomposite[j]=1;

           join(i,j);
        }
    }

    set<int>sets;
    for(int i=1;i<=sz(S);i++)sets.insert(find(i));

    set<int>::iterator it;
    for(it=sets.begin();it!=sets.end();it++){

        int mn=inf,letter;
        for(char c='a';c<='z';c++){
            if(occ[c]>=sz[*it] && occ[c]<mn){
                mn=occ[c];
                letter=c;
            }
        }
        if(mn==inf){cout<<"NO\n"; return 0;}

        occ[letter]-=sz[*it];

        letter_in_set[*it]=letter;

    }

    string res;
    for(int i=1;i<=sz(S);i++){

        char c=letter_in_set[find(i)];
        res+=c;

    }

    cout<<"YES\n";
   cout<<res<<"\n";

}
