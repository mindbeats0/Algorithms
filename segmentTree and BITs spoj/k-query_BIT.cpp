#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
const int N = 30000;
pair<int,int> arr[N+5];
pair<pair<int,int>, pair<int,int> >queries[200000+5];
int ans[200000+5],Tree[4*N];
 
int S,E,IND;
void update(int idx,int s,int e){
	if(s>IND || e<IND)return ;
	if(s==e){
		Tree[idx]++;
		return;
	}
	int mid = (s+e)/2;
	update(idx*2,s,mid);
	update(idx*2+1,mid+1,e);
	Tree[idx] = Tree[idx*2]+Tree[idx*2+1];
}
 
int query(int idx,int s,int e){
	if(s>E || e<S)return 0;
	if(s>=S && e<=E){
		return Tree[idx];
	}
	int mid = (s+e)/2;
	return query(idx*2,s,mid)+query(idx*2+1,mid+1,e);
}
int main(){
	int n,q,x,y,k,id;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i].first);
		arr[i].second=i;
	}
	scanf("%d",&q);
	for(int i=0;i<q;i++){
		scanf("%d%d%d",&x,&y,&k);
		x--; y--;
		queries[i] = mp (mp(k,i),mp(x,y));
	}
	sort(queries,queries+q);
	reverse(queries,queries+q);
	
	sort(arr,arr+n);
	
	int p = n-1;
	for(int i=0;i<q;i++){
		k=queries[i].first.first;
		id=queries[i].first.second;
		
		x=queries[i].second.first;
		y=queries[i].second.second;
		
		while(p>=0 && arr[p].first>k){
			IND = arr[p].second;
			update(1,0,n-1);
			p--;
		}
	
		S=x,E=y;
		ans[id] = query(1,0,n-1);
		
	}
	for(int i=0;i<q;i++)printf("%d\n",ans[i]);
}
 
