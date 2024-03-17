//CF: E. XOR and Favorite Number
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5;
const int MAXV=3e6;
int arr[MAXN+5];
#define BLOCK 1000
struct query{
    int L,R,id;
    const bool operator <(const query&other)const{
        if(L/BLOCK != other.L/BLOCK)return L/BLOCK < other.L/BLOCK;
        return R<other.R;
    }
}Q[MAXN+5];

int acc[MAXN+5]; // acc xor
int freq[MAXV+5];
long long ans[MAXN+5];
int main(){
   int n,m,k;
   scanf("%d%d%d",&n,&m,&k);
   for(int i=1;i<=n;i++){
       scanf("%d",&arr[i]);
       acc[i] = acc[i-1]^arr[i];
   }


   for(int i=0;i<m;i++){
       scanf("%d%d",&Q[i].L,&Q[i].R);
       Q[i].id= i;
   }
   sort(Q,Q+m);


   int l=1,r=1;
   freq[0]++;
   freq[acc[1]]++;
   long long res = arr[1]==k;

   for(int i=0;i<m;i++){

       int L = Q[i].L;
       int R = Q[i].R;
       int id = Q[i].id;


        while(r<R){
           r++;
           res += freq[acc[r]^k];
           freq[acc[r]]++;
       }

       while(r>R){
           freq[acc[r]]--;
           res -= freq[acc[r]^k];
           r--;
       }

//cout<<res<<"***\n";


        while(l<L){
           freq[acc[l-1]]--;
           res -= freq[acc[l-1]^k];

           l++;
       }

       while(l>L){
           l--;

           res += freq[acc[l-1]^k];
           freq[acc[l-1]]++;

       }

     //  cout<<L<<" "<<R<<"  : "<<res<<endl;
       ans[id] = res;
   }

   for(int i=0;i<m;i++){
      printf("%I64d\n",ans[i]);
   }
   return 0;

}

