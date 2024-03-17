/*
kingofnumbers http://codeforces.com/blog/entry/9204
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
pair<int,int>arr[MAXN+5];
const int MS = 1000;
// divide array into 100 blocks each one with size 1000
vector<int> acc[105];
int main(){
    int n,m,x,y,k;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i].first);
        arr[i].second=i;
    }
    sort(arr+1,arr+n+1);

    for(int i=1;i<=n;i++)
        acc[(i-1)/MS].push_back(arr[i].second);

    for(int b=0;b<100;b++){
		sort(acc[b].begin(),acc[b].end());
    }

    while(m--){
        scanf("%d%d%d",&x,&y,&k);
        int temp=0;
        for(int b=0;b<100;b++){
			int now=upper_bound(acc[b].begin(),acc[b].end(),y)-lower_bound(acc[b].begin(),acc[b].end(),x);

            if(temp + now>= k){
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
                temp += now;
            }
        }
    }
    return 0;
}
