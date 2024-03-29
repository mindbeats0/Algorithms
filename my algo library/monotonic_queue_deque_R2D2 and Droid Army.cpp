#include <bits/stdc++.h>
using namespace std;
const int N=1e5;
int arr[N+5][5];

typedef pair<int,int>pii;
#define mp make_pair

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,m,k;
    cin>>n>>m>>k;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>arr[i][j];

    int res[5]={};



     deque<pii> Q[5];
     int s=0,e=0,max_len=0;
     while(e<n){

            for(int i=0;i<m;i++){
                while(Q[i].size() && arr[e][i]>=Q[i].back().first)Q[i].pop_back();
                Q[i].push_back(mp(arr[e][i],e));
            }

            for(int i=0;i<m;i++){
                while(Q[i].size() && Q[i].front().second<s)Q[i].pop_front();
            }


            int tot=0;  for(int i=0;i<m;i++)tot+=Q[i].front().first;
            if(e-s+1>max_len && tot<=k){
                max_len=e-s+1;
                for(int i=0;i<m;i++)res[i]=Q[i].front().first;

            }

            if(tot<=k)e++;
            else s++;
            if(s>e)e=s;

     }


    for(int j=0;j<m;j++){
        cout<<res[j]<<" \n"[j==m-1];
    }
}


