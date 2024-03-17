//https://codeforces.com/contest/464/problem/B
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
const int inv=(1<<30);
int p[8][3];
bool flag=0;
vector<int>adj[8];
long long abss(long long a){
	if(a>0)return a;
	return a*-1;
}
long long getdistance(int i,int j){
	long long x1,y1,z1,x2,y2,z2;
	
	x1=p[i][0];y1=p[i][1];z1=p[i][2];
	x2=p[j][0];y2=p[j][1];z2=p[j][2];
	
	return abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2)+abs(z1-z2)*abs(z1-z2);
}
void print(){
	printf("YES\n");
	for(int i=0;i<8;i++){
		for(int j=0;j<3;j++){
			printf("%d",p[i][j]);
			if(j==2)printf("\n");
			else printf(" ");
		}
	}
}
bool isdistinct(){
	for(int i=0;i<8;i++)
		for(int j=i+1;j<8;j++)
			if(p[i][0]==p[j][0] && p[i][1]==p[j][1]  && p[i][2]==p[j][2] )return 0;
	return 1;
}

bool getneighbours(){
	
	vector<long long>points[8];
	
	//find the distance l
	long long mini=1000000000000000000;
	for(int i=0;i<8;i++){
		for(int j=i+1;j<8;j++){
			mini=min(mini,getdistance(i,j));
		}
	}
	//push the neighbours
	long long l;
	for(int i=0;i<8;i++){	
		for(int j=i+1;j<8;j++){
			l=getdistance(i,j);
			if(l==mini){points[i].push_back(j);points[j].push_back(i);}
		}
	}
	
	// check that each point has 3 neighbours points at a distance l
	for(int i=0;i<8;i++){
		if((int)points[i].size()!=3)
			return 0;
	}
	
	// check that each 3 neighbour segments are perpendicular
	for(int i=0;i<8;i++){	
	
		for(int u=0;u<3;u++)
			for(int v=u+1;v<3;v++){
				
				long long s1=getdistance(i,points[i][u]);
				long long s2=getdistance(i,points[i][v]);
				long long s3=getdistance(points[i][u],points[i][v]);
				
				if(s1+s2!=s3)return 0;
			
			}
	}
	
	return 1;
}
bool iscube(){
	
	// check all the points are distinct
	if(!isdistinct())return 0;
	
	//get for each point 3 points
	if(!getneighbours())return 0;
	
	return 1;	
}
void solve(int ind){
	if(flag)return;
	if(!ind){solve(ind+1);return;} // no need to permute the first point 
	if(ind==8){	
		if(iscube())
			{flag=1;print();}
		return;
	}
	
	do{

		solve(ind+1);
	}while(next_permutation(p[ind],p[ind]+3));
	
	return;
}
int main(){
	for(int i=0;i<8;i++){
		for(int j=0;j<3;j++)
			scanf("%d",&p[i][j]);
		sort(p[i],p[i]+3);
	}
	
	solve(0);
	
	if(!flag)printf("NO\n");
	return 0;
}