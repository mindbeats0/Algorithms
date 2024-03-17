//https://codeforces.com/contest/319/problem/C
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100000;
const ll INF = LONG_LONG_MIN;
ll a[MAXN+5],b[MAXN+5],dp[MAXN+5];
int N;
vector<ll>start;
vector<int>id;
 
ll getIntersect(ll m1,ll c1){
    int idx=id.back();
    ll m2=b[idx];
    ll c2=dp[idx];
    return ceil((double)(c2-c1)/(m1-m2));
}
int main(){
    //freopen("kalila.in","r",stdin);
   // freopen("kalilaNADA.out","w",stdout);
 
    cin>>N;
    for(int i=0;i<N;i++)cin>>a[i];
    for(int i=0;i<N;i++)cin>>b[i];
 
 
 
    start.push_back(INF);
    id.push_back(0);
 
    for(int i=1;i<N;i++){
   //for(int j=0;j<i;j++)dp[i]=min(dp[i],dp[j]+b[j]*a[i]);
 
        int idx=upper_bound(start.begin(),start.end(),a[i])-start.begin()-1;
        int j=id[idx];
        dp[i]= dp[j]+b[j]*a[i];
 
       // insert the line
       while(getIntersect(b[i],dp[i])<start.back())
            start.pop_back(),id.pop_back();
 
       start.push_back(getIntersect(b[i],dp[i]));
       id.push_back(i);
 
    }
    cout<<dp[N-1]<<"\n";
}