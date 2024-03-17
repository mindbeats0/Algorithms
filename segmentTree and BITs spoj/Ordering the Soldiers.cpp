#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
 
const int MAXB=1<<18;
int arr[MAXN+5],res[MAXN+5];
 
int tree[2*MAXB];
void update(int idx,int val){
	for(int x=idx;x<=MAXB;x+=x&-x)
		tree[x]+=val;
}
int query(int idx){
	int ret=0;
	for(int x=idx;x>0;x-=x&-x)
		ret+=tree[x];
	return ret;
}
int find(int cumFre){
	int res=-1;
	int st=0,bitMask=MAXB;
	while(bitMask!=0 && st<=MAXB){
		int idx=st+bitMask;
		//each time its equal to cumFre
		//my result maybe tIdx or less
		if(cumFre==tree[idx])res=idx;
		else if(cumFre>tree[idx]){
			st=idx;
			cumFre-=tree[idx];
		}
		bitMask >>= 1;
	}
	return res;
}
int main(){
	int tc,n;
	scanf("%d",&tc);
	while(tc--){
		
		scanf("%d",&n);
	    for(int i=1;i<=n;i++)
			scanf("%d",&arr[i]);
	    
	    for(int i=1;i<=n;i++)
			update(i,1);
			
	    for(int i=n;i>0;i--){
			int pos=i-arr[i];
			int idx=find(pos);
			res[i]=idx;
			update(idx,-1);
		}
		
	    
		for(int i=1;i<=n;i++){
			if(i>1)printf(" ");
			printf("%d",res[i]);
		}
		printf("\n");
	}
}
