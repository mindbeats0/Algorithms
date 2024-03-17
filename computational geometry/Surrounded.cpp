//https://codeforces.com/contest/190/problem/B
#include <bits/stdc++.h>
using namespace std;
 
int x[2],y[2],r[2];
int main(){
    for(int i=0;i<2;i++)
        cin>>x[i]>>y[i]>>r[i];
 
 
    //double dist=sqrt((double)abs(x[0]-x[1])*(double)abs(x[0]-x[1]) + (double)abs(y[0]-y[1])*(double)abs(y[0]-y[1]) );
    double dist=hypot((double)abs(x[0]-x[1]),(double)abs(y[0]-y[1]) );
    //("%.15lf  %.15lf\n",dist,dist2);
 
    if(dist<(double)r[0]+r[1]){
         int R=max(r[0],r[1]);
         int rr=min(r[0],r[1]);
         if(dist<=R-rr){
            //printf("%.15lf\n",((double)R-dist-(double)rr)/2.0);
             cout << (fixed) << setprecision(15)<<((double)R-dist-(double)rr)/2.0<<endl;
 
         }
         else
           // printf("0\n");
           cout<<"0"<<endl;
    }
    else{
        dist-=(r[0]+r[1]);
        dist/=2.0;
       // printf("%.15lf\n",dist);
       cout << (fixed) << setprecision(15)<<dist<<endl;
    }
 
 
}