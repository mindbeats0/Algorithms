#include <bits/stdc++.h>
using namespace std;
int arr[2000005],freq[100],res[2000005],n;
void counting_sort(){
    memset(freq,0,sizeof freq);
    int R=-1,L=100,k;
     for(int i=0;i<n;i++){
        R=max(R,arr[i]);
        L=min(L,arr[i]);
     }
     k = R-L+1;
     for(int i=0;i<n;i++) // freq of shifted value
        freq[arr[i]-L]++;

     for(int i=1;i<k;i++)
        freq[i] += freq[i-1];

    for(int i=n-1;i>=0;i--){
        res[freq[arr[i]-L]-1] = arr[i];
        freq[arr[i]-L]--;
    }

    for(int i=0;i<n;i++)
        arr[i]=res[i];
}
int main(){
    while(scanf("%d",&n),n){
        for(int i=0;i<n;i++)
            scanf("%d",&arr[i]);
        counting_sort();

        for(int i=0;i<n;i++){
            printf("%d",arr[i]);
            if(i==n-1)printf("\n");
            else printf(" ");
        }
    }

}
