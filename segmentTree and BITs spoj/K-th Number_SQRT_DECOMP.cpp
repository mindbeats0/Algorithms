/*
kingofnumbers http://codeforces.com/blog/entry/9204
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
pair<int,int>arr[MAXN+5];
// divide array into 100 blocks each one with size 1000
const int MS = 1000;
int acc[105][MAXN+5];
int main(){
    int n,m,x,y,k;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i].first);
        arr[i].second=i;
    }
    sort(arr+1,arr+n+1);

    for(int i=1;i<=n;i++)
        acc[(i-1)/MS][arr[i].second]=1;

    for(int b=0;b<100;b++){
        for(int i=1;i<=n;i++){
            acc[b][i] += acc[b][i-1];
        }
    }
   // the blocks are sorted according to values.
    while(m--){
        scanf("%d%d%d",&x,&y,&k);
        int temp=0;
        for(int b=0;b<100;b++){
            if(temp + acc[b][y]-acc[b][x-1] >= k){
                for(int i=b*MS;i<(b+1)*MS;i++){
                    if(arr[i+1].second >=x && arr[i+1].second <=y)temp++;
                    if(temp == k){
                        printf("%d\n",arr[i+1].first);
                        break;
                    }
                }
                break;
            }
            else{
                temp += acc[b][y]-acc[b][x-1];
            }
        }
    }
    return 0;
}
