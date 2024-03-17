//https://codeforces.com/contest/166/problem/B
#include <bits/stdc++.h>
using namespace std;
#define sz(a) ((int)(a).size())
struct Point{
    int x,y;
    const bool operator == (const Point &other)const{
        return x==other.x && y==other.y;
    }
    const bool operator < (const Point &other)const{
        return x < other.x || x == other.x  && y<other.y;
    }
}PIVOT;

long long dist2(Point p1,Point p2){
    long long X=p1.x-p2.x,Y=p1.y-p2.y;
    return X*X + Y*Y ;

}

long long cross(Point p1,Point p2,Point p3){
    return (long long )(p2.x-p1.x) * (p3.y-p1.y) - (long long )(p2.y-p1.y) * (p3.x-p1.x);
}
bool angCmp(const Point &a,const Point &b){
    long long _cross=cross(PIVOT,a,b);
    if(_cross==0)return dist2(PIVOT,a)<dist2(PIVOT,b);
    return _cross>0;
}
int main(){


   int n,m;
   cin>>n;
   vector<Point>A(n);

   for(int i=0;i<n;i++)cin>>A[i].x>>A[i].y;
   sort(A.begin(),A.end());
   A.resize(unique(A.begin(),A.end())-A.begin());


   cin>>m;
   vector<Point>B(m);
   for(int i=0;i<m;i++)cin>>B[i].x>>B[i].y;
   sort(B.begin(),B.end());
   B.resize(unique(B.begin(),B.end())-B.begin());


   PIVOT=A[0];
   for(int i=0;i<sz(A);i++)
      if(A[i].y<PIVOT.y || A[i].y==PIVOT.y && A[i].x<PIVOT.x  )PIVOT=A[i];
   for(int i=0;i<sz(B);i++)
      if(B[i].y<PIVOT.y || B[i].y==PIVOT.y && B[i].x<PIVOT.x  )PIVOT=B[i];


   if(count(B.begin(),B.end(),PIVOT)){cout<<"NO\n"; return 0;}

   sort(A.begin(),A.end(),angCmp);
   sort(B.begin(),B.end(),angCmp);


    if(cross(A[0],A[1],B[0])<=0 || cross(A[0],A[sz(A)-1],B[sz(B)-1])>=0 ){cout<<"NO\n";return 0;}

   int i=1,j=0;
   while(i<sz(A)-1 && j<sz(B)){


     long long _cross1=cross(PIVOT,A[i],B[j]);
     long long _cross2=cross(PIVOT,A[i+1],B[j]);
     if(_cross1>=0 && _cross2<=0){

         if(cross(A[i],A[i+1],B[j])<=0){cout<<"NO\n";return 0;}
         j++;
     }
     else if(_cross1>0 && _cross2>0)
         i++;
     else if(_cross1<0 && _cross2<0)
         j++;


   }
   cout<<"YES\n";

   return 0;
}