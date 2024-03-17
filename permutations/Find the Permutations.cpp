#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
ll F[25],C[25][25],dp[25][25];
ll fact(int x){
    if(F[x]!=-1)return F[x];
    if(!x)return 1;
    return F[x] = x*fact(x-1);
}
ll comb(int n,int r){
    if(C[n][r]!=-1)return C[n][r];
    if(n==r || r==0)return 1;
    if(r==1)return n;


    return C[n][r] = comb(n-1,r-1) + comb(n-1,r);
}
ll solve(int k,int rem){
    if(!k)return !rem;

    if(dp[k][rem]!=-1)return dp[k][rem];
    ll ret=0;
    for(int i=1;i<=rem;i++){
        ret += comb(rem-1,i-1) * fact(i-1) *solve(k-1,rem-i);
    }
    return dp[k][rem]=ret;
}
int main(){
    int n,k;
    while(scanf("%d%d",&n,&k),n){
        int c = n-k;
        memset(F,-1,sizeof F);
        memset(C,-1,sizeof C);
        memset(dp,-1,sizeof dp);
        printf("%llu\n",solve(c,n));
    }
}
