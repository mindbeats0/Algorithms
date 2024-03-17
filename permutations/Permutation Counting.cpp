#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
ll dp[1010][1010];
int main(){
    dp[0][0]=1;
    for(int i=1;i<=1000;i++){
        for(int k=0;k<i;k++){
            dp[i][k] = dp[i-1][k];
            dp[i][k] = (dp[i][k] + k*dp[i-1][k]%mod)%mod;
            if(k)dp[i][k] = (dp[i][k] + ((i-1) - (k-1))*dp[i-1][k-1]%mod)%mod;
        }
    }
    int N,K;
    while(scanf("%d%d",&N,&K)!=EOF){
        printf("%lld\n",dp[N][K]);

    }
}
