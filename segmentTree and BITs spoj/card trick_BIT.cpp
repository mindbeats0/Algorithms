#include <bits/stdc++.h>
using namespace std;
const int MAXN=20000;
const int MAXB=1<<15;
int ans[MAXN+5];
int tree[2*MAXB+5];
void update(int idx,int val){
	for(int x=idx;x<=MAXB;x+=x&-x)
		tree[x]+=val;
}
int find(int cumFre){
	int res=-1;
	int idx=0,bitMask=MAXB;
	while(bitMask!=0 && idx<=MAXB){
		int tIdx=idx+bitMask;
		//each time its equal to cumFre
		//my result maybe tIdx or less
		if(cumFre==tree[tIdx])res=tIdx;
		else if(cumFre>tree[tIdx]){
			idx=tIdx;
			cumFre-=tree[tIdx];
		}
		bitMask >>= 1;
	}
	return res;
}
int main(){
	int tc,n;
	scanf("%d",&tc);
	while(tc--){
		memset(ans,0,sizeof ans);
		memset(tree,0,sizeof tree);
		scanf("%d",&n);
	    
	    for(int i=1;i<=n;i++)update(i,1);
	    // my answer array is zero based
	    // in bit its one based
	    int pos=0,sz=n;
	    for(int i=1;i<=n;i++){
			pos=(pos+i)%sz;
			int idx = find(pos+1);
	
			ans[idx-1]=i;
		
			update(idx,-1);
		
			sz--;
		}
	    
	    
		for(int i=0;i<n;i++){
			if(i)printf(" ");
			printf("%d",ans[i]);
		}
		printf("\n");
	}
}
