/*
	TASK: agrinet
	LANG: C++
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX=10000;
int parent[MAX];
int height[MAX];
int n;
void init()
{
	memset(height,0,sizeof(height));
	for(int i=0;i<n;i++)
		parent[i]=i;
	return;

}
int find(int e)
{
	if(parent[e]==e)
		return e;
	return parent[e]= find(parent[e]);
}
void join(int e1,int e2)
{
	e1=find(e1);e2=find(e2);

	if(e1==e2)return;

	if (height[e1]<height[e2])swap(e1,e2);
	if (height[e1]==height[e2])height[e1]++;

	parent[e2]=e1;
}
struct node{
	int from;
	int to;
	int cost;
	bool operator <(const node & an)const
	{
		return cost<an.cost;
	}
	node(int a,int b,int c)
	{
		from=a;
		to=b;
		cost=c;
	}
	node(){}
};
vector<node> edges;
int main()
{
	freopen("agrinet.in","r",stdin);
	freopen("agrinet.out","w",stdout);
	cin>>n;
	int cost;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>cost;
			if(i!=j)
			{
				edges.push_back(node(i,j,cost) );
			}
		}
	}
	sort(edges.begin(),edges.end());
	init();

	int tot=0;
	for(int i=0;i<(int)edges.size();i++){
		if (find(edges[i].from)!=find(edges[i].to)){
			tot+=edges[i].cost;
			join(edges[i].from,edges[i].to);
		}
	}
	cout<<tot<<endl;
	return 0;
}

