//https://codeforces.com/contest/18/problem/A
#include <bits/stdc++.h>
using namespace std;

int x[3],y[3];

bool ishyp(int i,int j){
    int k;for(k=0;k==i || k==j;k++);

    int c=abs(x[i]-x[j])*abs(x[i]-x[j]) + abs(y[i]-y[j])*abs(y[i]-y[j]);
    int a=abs(x[i]-x[k])*abs(x[i]-x[k]) + abs(y[i]-y[k])*abs(y[i]-y[k]);
    int b=abs(x[j]-x[k])*abs(x[j]-x[k]) + abs(y[j]-y[k])*abs(y[j]-y[k]);

    if(c==a+b && a && b && c){
            /*cout<<x[i]<<" "<<y[i]<<endl;
            cout<<x[j]<<" "<<y[j]<<endl;
            cout<<x[k]<<" "<<y[k]<<endl;
            cout<<a<<" "<<b<<" "<<c<<endl;*/
            return true;
    }
    return false;
}

int main(){
    for(int i=0;i<3;i++)cin>>x[i]>>y[i];

    for(int i=0;i<3;i++)
        for(int j=i+1;j<3;j++)
            if(ishyp(i,j)){cout<<"RIGHT\n";  return 0;}

    for(int a=0;a<3;a++){

       x[a]++;
       for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)
            if(ishyp(i,j)){cout<<"ALMOST\n"; return 0;}
       x[a]--;


       x[a]--;
       for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)
            if(ishyp(i,j)){cout<<"ALMOST\n"; return 0;}
       x[a]++;


      y[a]++;
       for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)
            if(ishyp(i,j)){cout<<"ALMOST\n"; return 0;}
       y[a]--;


       y[a]--;
       for(int i=0;i<3;i++)for(int j=i+1;j<3;j++)
            if(ishyp(i,j)){cout<<"ALMOST\n"; return 0;}
       y[a]++;
   }
   cout<<"NEITHER\n";
   return 0;
}