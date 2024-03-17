//https://codeforces.com/contest/340/problem/B
#include <bits/stdc++.h>
using namespace std;
#define eps 1e-9

struct point{
    int x,y;
};
point arr[305];


double area(point i, point j,point k){
    int ax=j.x-i.x,ay=j.y-i.y;
    int bx=k.x-j.x,by=k.y-j.y;

    return (ax*by-bx*ay)*0.5;
}

int main(){
     int n;
     cin>>n;
     for(int i=0;i<n;i++)cin>>arr[i].x>>arr[i].y;

     double res=0,mx,mn;
     for(int i=0;i<n;i++){
         for(int j=i+1;j<n;j++){

              mn=0,mx=0;
              for(int k=0;k<n;k++){
                   if(k==i || k==j)continue;
                   double ret=area(arr[i],arr[j],arr[k]);
                   mx=max(mx,ret);
                   mn=min(mn,ret);
              }

              if(mx>eps && mn<-eps)res=max(res,mx+abs(mn));

         }
     }
     cout<<(fixed)<<setprecision(9)<<res<<"\n";
}