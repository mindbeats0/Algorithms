#include <bits/stdc++.h>
using namespace std;
const int MAXN=20000;
int ans[MAXN+5];
int Tree[4*MAXN];

void build(int idx,int s,int e){
	if(s==e){
		Tree[idx]=1;
		return ;
	}
	int mid = (s+e)>>1;
	build(idx*2,s,mid);
	build(idx*2+1,mid+1,e);
	Tree[idx]=Tree[idx*2]+Tree[idx*2+1];
}

void update(int idx,int s,int e,int qi){
	
	if(s>qi || e<qi)return ;
	if(s==e){
		Tree[idx]=0;
		return ;
	}
	int mid = (s+e)>>1;
	update(idx*2,s,mid,qi);
	update(idx*2+1,mid+1,e,qi);
	Tree[idx]=Tree[idx*2]+Tree[idx*2+1];
}

int query(int idx,int s,int e,int k){
	
	if(s==e)
		return s ;
	
	int left = Tree[idx*2];
	
	
	int mid = (s+e)>>1;
	if(left>=k)return query(idx*2,s,mid,k);
	else  return query(idx*2+1,mid+1,e,k-left);
}
int main(){
	int tc,n;
	scanf("%d",&tc);
	while(tc--){
		memset(ans,0,sizeof ans);
		scanf("%d",&n);
	    build(1,0,n-1);
	    
	    int pos=0,sz=n;
	    for(int i=1;i<=n;i++){
			pos=(pos+i)%sz;
			int idx = query(1,0,n-1,pos+1);
			ans[idx]=i;
			update(1,0,n-1,idx);
			
			sz--;
		}
	    
	    
		for(int i=0;i<n;i++){
			if(i)printf(" ");
			printf("%d",ans[i]);
		}
		printf("\n");
	}
}
