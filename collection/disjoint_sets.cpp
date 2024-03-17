#include <bits/stdc++.h>
using namespace std;
const int MAX=10000;
int parent[MAX];
int height[MAX];
int sz[MAX];//optional
int n;
void init()
{
	memset(height,0,sizeof(height));
	for(int i=0;i<n;i++)
		parent[i]=i,height[i]=1,sz[i]=1;
	return;

}
int find(int e)
{
	if(parent[e]==e) return e;

	return parent[e]= find(parent[e]);
}
void join(int e1,int e2)
{
	e1=find(e1);
        e2=find(e2);

	if(e1==e2) return;

	if (height[e1]<height[e2])swap(e1,e2);
	if (height[e1]==height[e2]) height[e1]++;

	parent[e2]=e1;
	sz[e1] += sz[e2];
}

