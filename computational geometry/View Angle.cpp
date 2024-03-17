//https://codeforces.com/contest/257/problem/C
#include <cstdio>
#include <cmath>
#include <algorithm>
#define PI 3.14159265
using namespace std;
const double eps = 1e-9;
double arr[100000];
int main(){
	int n,x,y;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&x,&y);
		double angle=atan2(y,x);
		if(angle<0)angle+=2*PI;
		arr[i]=angle; 
	}
	sort(arr,arr+n);
	
	double res=0;
	for(int i=0;i<n;i++){
		double angle1=arr[i];
		double angle2=arr[(i+1)%n];
		
		double angle=angle2-angle1; if(angle<0)angle+=2*PI;
		
		res=max(res,angle);
	}
	
	res=2*PI-res;
 
	
	if(res==2*PI)printf("0\n");
	else printf("%.9lf\n",(res*180)/PI);
    
	return 0;
}