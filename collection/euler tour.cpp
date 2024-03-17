#include <bits/stdc++.h>
using namespace std;
typedef pair<int,bool> ii;
vector<ii> AdjList[100];
list<int>cyc;

int CNT=0;

void eulerTour(list<int>::iterator i, int u){
	//printf("%d **\n",u);
	for(int j=0;j<AdjList[u].size();j++){
		ii v = AdjList[u][j];
		if(v.second){
			v.second=0;
			for(int k=0;k<AdjList[v.first].size();k++){
				ii uu = AdjList[v.first][k];
				if(uu.first == u && uu.second){
					uu.second = 0;
					break;
				}
			}
			//printf("%d -------%d\n",v.first,v.second);
			//if(CNT==6)return;
			//CNT++;
			eulerTour(cyc.insert(i,u),v.first);
		}
	}
//	for(list<int>::iterator it = cyc.begin();it != cyc.end();it++)
	//	printf("%d\n",*it);
		
	//	CNT++;
	//	if(CNT==6)return ;
}
int main(){
	int V,E,a,b;
	scanf("%d%d",&V,&E);
	for(int i=0;i<E;i++){
		scanf("%d%d",&a,&b);
		AdjList[a].push_back(make_pair(b,1));
		AdjList[b].push_back(make_pair(a,1));
	}
	int A = 3; // A is the start node
    cyc.clear();
    eulerTour(cyc.begin(),A);
    for(list<int>::iterator it = cyc.begin();it != cyc.end();it++)
		printf("%d\n",*it);
}
