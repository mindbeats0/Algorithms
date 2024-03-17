#include <bits/stdc++.h>
using namespace std;
struct node{
	int sum,left,right,max;
	node(){}
	node(int sum,int left,int right,int max):sum(sum),left(left),right(right),max(max){}
};
const int N = 50000;
const int INF = 6e8;
node invalid;
int arr[N+5];
node Tree[4*N];
int IND,VAL,S,E;
node merge(node c1,node c2){
	node ret;
	
	if(c1.sum == -INF)return c2;
	if(c2.sum == -INF)return c1;
	
	ret.sum =  c1.sum + c2.sum;
	ret.left = max(c1.left,c1.sum + c2.left);
	ret.right = max(c2.right ,c2.sum + c1.right);
 
	ret.max = max(c1.max,c2.max);
	ret.max = max(ret.max,c1.right+c2.left);
	return ret;
}
void build(int idx,int s,int e){
	if(s==e){
		
		Tree[idx]=node(arr[s],arr[s],arr[s],arr[s]);
		return ;
	}
	
	int mid = (s+e)/2;
	build(idx*2,s,mid);
	build(idx*2+1,mid+1,e);
	
	Tree[idx] = merge(Tree[idx*2],Tree[idx*2+1]);
}
void update(int idx,int s,int e){
	if(s>IND || e<IND)return;
	if(s==e){
		Tree[idx]=node(VAL,VAL,VAL,VAL);
		return ;
	}
	
	int mid = (s+e)/2;
	update(idx*2,s,mid);
	update(idx*2+1,mid+1,e);
	Tree[idx] = merge(Tree[idx*2],Tree[idx*2+1]);
}
node query(int idx,int s,int e){
	if(s>E || e<S)return invalid;
	if(s>=S && e<=E)
		return Tree[idx];
	
	int mid = (s+e)/2;
	return merge(query(idx*2,s,mid),query(idx*2+1,mid+1,e));
	
}
 
int main(){
	invalid=node(-INF,-INF,-INF,-INF);

	int n,m;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	build(1,0,n-1);
	scanf("%d",&m);
	int op,x,y;
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&op,&x,&y);
		if(!op){//A[x] = y;
			IND=x-1; VAL=y;
			update(1,0,n-1);
		}
		else{
			S=x-1,E=y-1;
			printf("%d\n",query(1,0,n-1).max);
			
		}
	}
	return 0;	
}
