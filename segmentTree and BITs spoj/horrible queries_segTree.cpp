#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5;
typedef long long ll;
ll Tree[4*MAXN],Lazy[4*MAXN];

void relax(int idx,int s,int e){
	Tree[idx]+=Lazy[idx]*(e-s+1);
	if(s!=e){
		Lazy[idx*2]+=Lazy[idx];
		Lazy[idx*2+1]+=Lazy[idx];
	}
	Lazy[idx]=0;
}
void update(int idx,int s,int e,int qs,int qe,int val){
	relax(idx,s,e);
	if(s>qe || e<qs)return;
	if(s>=qs && e<=qe){
		Lazy[idx] += val;
		relax(idx,s,e);
		return ;
	}
	int mid =(s+e)>>1;
	update(idx*2,s,mid,qs,qe,val);
	update(idx*2+1,mid+1,e,qs,qe,val);
	Tree[idx] = Tree[idx*2]+Tree[idx*2+1];
}
ll query(int idx,int s,int e,int qs,int qe){
	relax(idx,s,e);
	if(s>qe || e<qs)return 0;
	if(s>=qs && e<=qe){
		return Tree[idx];
	}
	int mid =(s+e)>>1;
	return query(idx*2,s,mid,qs,qe)+query(idx*2+1,mid+1,e,qs,qe);
	
}
int main(){
	int tc,n,m,op,x,y,v;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d%d",&n,&m);
		memset(Tree,0,sizeof Tree);
		memset(Lazy,0,sizeof Lazy);
		for(int i=0;i<m;i++){
			scanf("%d",&op);
			if(!op){
				scanf("%d%d%d",&x,&y,&v);
				x--; y--;
				update(1,0,n-1,x,y,v);
			}
			else{
				scanf("%d%d",&x,&y);
				x--; y--;
				ll ans = query(1,0,n-1,x,y);
				printf("%lld\n",ans);
			}
		}
		
	}
}
