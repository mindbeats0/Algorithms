//https://codeforces.com/contest/250/problem/D
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
struct point{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}
};
struct line{
 
};
int  A[100005],B[100005];
int l[100005];
 
double dist(point a,point b){
    return hypot((double)abs(a.x-b.x),(double)abs(a.y-b.y));
}
int main(){
    int n,m,a,b;
    cin>>n>>m>>a>>b;
 
    for(int i=0;i<n;i++)cin>>A[i];
    for(int i=0;i<m;i++)cin>>B[i];
    for(int i=0;i<m;i++)cin>>l[i];
 
 
 
    double mini=1e15;
    pair<int,int>res;
    for(int i=0;i<m;i++){
 
        int _y=(double)B[i]*a/b;
 
 
        int idx=upper_bound(A,A+n,_y)-A;
 
        if(idx==n)idx--;
        else if(idx-1>=0 &&abs(_y-A[idx-1])<abs(_y-A[idx]))idx--;
 
        point P=point(a,A[idx]);
 
        double cur=l[i]+dist(point(b,B[i]),P)+dist(P,point(0,0));
        if(cur<mini){
            mini=cur;
            res=make_pair(idx+1,i+1);
        }
       // printf("%lf **\n",res);
    }
    printf("%d %d\n",res.first,res.second);
}