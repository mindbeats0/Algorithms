#include <bits/stdc++.h>
using namespace std;
const int N=100000;
int arr[N+5],acc[N+5],start[N+5],endd[N+5],Tree[4*N];
 
int S,E;
void build(int idx,int s,int e){
	if(s==e){
		Tree[idx]=acc[s];
		return ;
	}
 
	int mid=(s+e)/2;
	build(idx*2,s,mid);
	build(idx*2+1,mid+1,e);
 
	Tree[idx]=max(Tree[idx*2],Tree[idx*2+1]);
}
 
int query(int idx,int s,int e){
 
	if(s>=S && e<=E)
		return Tree[idx];
	if(s>E || e<S)return 0;
 
	int mid=(s+e)/2;
	return max( query(idx*2,s,mid),query(idx*2+1,mid+1,e) );
 
}
 
int main(){
	int n,q;
	while(1){
		scanf("%d",&n);
		if(!n)return 0;
		scanf("%d",&q);
 
		int R=0;
		map<int,int>mp;
		memset(arr,-1,sizeof arr);
		memset(acc,0,sizeof acc);
		for(int i=1;i<=n;i++){
			scanf("%d",&arr[i]);
			mp[arr[i]];
		}
		
		for(auto it=mp.begin();it!=mp.end();it++)
			it->second=R++;
			
		for(int i=1;i<=n;i++)
			arr[i]=mp[arr[i]];
 
		for(int i=1;i<=n;i++){
			if( arr[i-1]!=arr[i]){
				acc[i]=1;
				start[arr[i]]=i;
			}
			else acc[i]=acc[i-1]+1;
 
			if(arr[i+1]!=arr[i])
				endd[arr[i]]=i;
		}
		
		
		build(1,1,n);
		int x,y,res,res1,res2;
		for(int i=0;i<q;i++){
			scanf("%d%d",&x,&y);
			if(arr[x]==arr[y]){
				if(x==start[arr[x]])res=acc[y];
				else res=acc[y]-acc[x-1];
				printf("%d\n",res);
			}
			else if(arr[x]+1 == arr[y]){
				if(x==start[arr[x]])res1=acc[endd[arr[x]]];
				else res1=acc[endd[arr[x]]] - acc[x-1];
 
				res2=acc[y];
				printf("%d\n",max(res1,res2));
			}
			else{
 
				if(x==start[arr[x]])res1=acc[endd[arr[x]]];
				else res1=acc[endd[arr[x]]] - acc[x-1];
				res2=acc[y];
 
				res=max(res1,res2);
 
				S=start[arr[x]+1],E=endd[arr[y]-1];
				res=max(res,query(1,1,n));
				printf("%d\n",res);
 
			}
		}
 
 
	}
 
}
 
