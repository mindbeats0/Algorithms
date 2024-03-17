//https://codeforces.com/problemset/problem/507/B
#include <bits/stdc++.h>
using namespace std;
 
int main(){
	int r,x,y,xx,yy;
	cin>>r>>x>>y>>xx>>yy;
	
	if(x==xx && y==yy){printf("0\n"); return 0;}
	long long X=abs(xx-x);
	long long Y=abs(yy-y);
	
	long long len=sqrt(X*X+Y*Y);
	
	long long moves=len/(2*r);
	if(moves*2*r!=len || len*len!=X*X+Y*Y)moves++;
	
	
	cout<<moves<<"\n";
}