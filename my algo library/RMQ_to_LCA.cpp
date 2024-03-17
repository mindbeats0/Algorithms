#include <bits/stdc++.h>
using namespace std;

const int MAXN=150;
 void computeTree(int A[MAXN], int N, int T[MAXN])
  {
      int st[MAXN], i, k, top = -1;

      for (i = 0; i < N; i++)
      {
          k = top;
          while (k >= 0 && A[st[k]] > A[i])
              k--;

         if (k != -1)
              T[i] = st[k];
         if (k < top)
              T[st[k + 1]] = i;

          st[++k] = i;
          top = k;
      }
      T[st[0]] = -1;

      for(int i=0;i<10;i++){
            if(T[i]!=-1)
            cout<<A[i]<<" "<<A[T[i]]<<"\n";
      }
      cout<<"\n";
      for(int i=0;i<10;i++){
          cout<<T[i]<<" ";
      }
      cout<<"\n";

  }

int main(){
    int A[100],N,T[100];
    memset(A,0,sizeof A);
    memset(T,0,sizeof T);
    N=10;
    for(int i=0;i<10;i++)cin>>A[i];
    computeTree(A,N,T);
}
