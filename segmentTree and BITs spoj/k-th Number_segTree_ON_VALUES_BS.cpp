#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
const int INF = 1e9;
int arr[N+5];
vector<int>Tree[4*N];
int S,E,VAL;
void merge(vector<int>&res,vector<int>&a,vector<int>&b){
	int i=0,j=0;
	while(i<a.size() || j<b.size()){
		if(i==a.size())res.push_back(b[j++]);
		else if(j==b.size())res.push_back(a[i++]);
		else if(a[i] <= b[j] )res.push_back(a[i++]);
		else res.push_back(b[j++]);
	}
 
}
void build(int idx,int s,int e){
	if(s==e){
		Tree[idx].push_back(arr[s]);
		return ;
	}
	int mid = (s+e)/2;
	build(idx*2,s,mid);
	build(idx*2+1,mid+1,e);
	
	S=s,E=e;
	merge(Tree[idx],Tree[idx*2],Tree[idx*2+1]);
}
int query(int idx,int s,int e){
	if(s>E || e<S)return 0;
	if(s>=S && e<=E){
		return lower_bound(Tree[idx].begin(),Tree[idx].end(),VAL)-Tree[idx].begin();
	}
	int mid = (s+e)/2;
	return query(idx*2,s,mid)+query(idx*2+1,mid+1,e);	
}
 
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	
	build(1,0,n-1);
	int x,y,k;
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&x,&y,&k);
		S=x-1; E=y-1;
		int lo=-INF,hi=INF,mid,ans=-1;
		while(lo<=hi){
			mid = (lo+hi)/2;
			VAL = mid;
			int q=query(1,0,n-1);
			if(q<k){
				ans = mid;
				lo=mid+1; 
			}
			else 
				hi = mid-1;		
		}
		printf("%d\n",ans);
	}
	return 0;
}
