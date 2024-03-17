#include <bits/stdc++.h>
using namespace std;
const int MAXN=10000;
const int INF = 1e8;
int arr[MAXN+5];
struct node{
	int left,right,maxi,sum;
	node(){}
	node(int left,int right,int maxi,int sum):left(left),right(right),maxi(maxi),sum(sum){}
};
node Tree[4*MAXN];
 
node merge(node a, node b){
	if(a.left == -INF)return b;
	if(b.left == -INF)return a;
	node ret;
	ret.left = max(a.left , a.sum + b.left);
	ret.right = max(b.right , b.sum + a.right);
	
	ret.maxi = max(a.maxi,b.maxi);
	ret.maxi = max(ret.maxi, a.right + b.left);
	
	ret.sum = a.sum + b.sum;
	
	return ret;
}
void build(int idx,int s,int e){
	if(s==e){
		Tree[idx].left = arr[s];
		Tree[idx].right = arr[s];
		Tree[idx].maxi = arr[s];
		Tree[idx].sum = arr[s];
		return ;
	}
	int mid = (s+e)/2;
	build(idx*2,s,mid);
	build(idx*2+1,mid+1,e);
	Tree[idx] = merge(Tree[idx*2],Tree[idx*2+1]);
}
node query(int idx,int s,int e,int qs,int qe){
	if(s>qe || e<qs)return node(-INF,-INF,-INF,-INF);
	if(s>=qs && e<=qe)return Tree[idx];
	
	int mid = (s+e)/2;
	return merge ( query(idx*2,s,mid,qs,qe),query(idx*2+1,mid+1,e,qs,qe) );
}
int main(){
	int T,N,M,x1,y1,x2,y2;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=0;i<N;i++)
			scanf("%d",&arr[i]);
		build(1,0,N-1);
		scanf("%d",&M);
		for(int i=0;i<M;i++){
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1--;y1--;x2--;y2--;
			int res;
			if(y1<x2){
				res = query(1,0,N-1,x1,y1).right + query(1,0,N-1,x2,y2).left;
				if(y1+1<x2)res += query(1,0,N-1,y1+1,x2-1).sum;
			}
			else{
				res = query(1,0,N-1,x2,y1).maxi;
				res = max(res, query(1,0,N-1,x1,x2).right + query(1,0,N-1,x2,y2).left- arr[x2]); 
				res = max(res, query(1,0,N-1,x1,y1).right + query(1,0,N-1,y1,y2).left - arr[y1]);
			}
			printf("%d\n",res);
		}
	}
	return 0;
}
