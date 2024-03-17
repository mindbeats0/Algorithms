// 2D BIT
// http://www.spoj.com/problems/MATSUM/

#include <bits/stdc++.h>
using namespace std;
char buff[6];
int N;
long long bit[2000][2000];
int grid[2000][2000];
void update(int x,int y,int val){
	for(;x<2000;x+=x&-x){
		for(int ty=y;ty<2000;ty+=ty&-ty){
			bit[x][ty]+=val;
		}
	}
}

long long get(int x,int y){
	long long ret=0;
	for(;x>0;x-=x&-x){
		for(int ty=y;ty>0;ty-=ty&-ty){
			ret += bit[x][ty];
		}
	}
	return ret;
}

int main() {
	int T,x,y,num,x1,y1,x2,y2;
	scanf("%d",&T);
	while(T--){
		memset(bit,0,sizeof bit);
		memset(grid,0,sizeof grid);
		scanf("%d",&N);
		while(scanf("%s",buff),buff[0]!='E'){
			if(buff[1]=='E'){
			    scanf("%d%d%d",&x,&y,&num);
			    x++; y++;
			    update(x,y,-grid[x][y]);
			    grid[x][y]=num;
			    update(x,y,num);
			}
			else if(buff[1]=='U'){
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
				x1++; y1++; x2++; y2++;
				long long a = get(x2,y2);
				long long b = get(x1-1,y1-1);
				long long c = get(x1-1,y2);
				long long d = get(x2,y1-1);
				printf("%lld\n",a-c-d+b);
			}
		}
		printf("\n");
	}
	return 0;
}
