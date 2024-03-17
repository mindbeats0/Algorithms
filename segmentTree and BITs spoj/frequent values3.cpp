#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
const int INF = 1e6;

struct node{
	int s,e,pre,suf,result;
	node(){}
	node(int s,int e,int pre,int suf,int result)
	:s(s),e(e),pre(pre),suf(suf),result(result){}
	
	
};

node invalid;
int arr[N+5];
node Tree[4*N];
void merge(node&ret, node a, node b){
	
	if(a.s==-1){ret=b; return;}
	else if(b.s==-1){ret=a; return;}
	
	int s=a.s,mid=a.e,e=b.e; 
	if(arr[s] == arr[mid] && arr[mid] == arr[mid+1])ret.pre = a.pre + b.pre;
	else  ret.pre = a.pre;
	
	if(arr[e] == arr[mid+1] && arr[mid+1] == arr[mid])ret.suf = b.suf + a.suf;
	else  ret.suf = b.suf;
	
	ret.result = max(max(a.result,b.result),arr[mid]==arr[mid+1]?a.suf+b.pre:-INF);
	
	ret.s=a.s;
	ret.e=b.e;
	
}
void build(int idx,int s,int e){
	if(s==e){
		Tree[idx]=node(s,e,1,1,1);
		return ;
	}
	
	int mid = (s+e)/2;
	build(idx*2,s,mid);
	build(idx*2+1,mid+1,e);
	
	merge(Tree[idx],Tree[idx*2],Tree[idx*2+1]);
	
}
node query(int qs,int qe,int idx,int s,int e){
	if(s>qe || e<qs)return invalid;
	if(s>=qs && e<=qe)
		return Tree[idx];
	
	
	node ret;
	int mid = (s+e)/2;
	merge(ret,query(qs,qe,idx*2,s,mid),query(qs,qe,idx*2+1,mid+1,e));
	return ret;
	
}
 
int main(){
	invalid=node(-1,-1,-INF,-INF,-INF);

	int n,m;
	while(scanf("%d",&n),n){
		scanf("%d",&m);
		for(int i=0;i<n;i++)
			scanf("%d",&arr[i]);
		build(1,0,n-1);
		int x,y;
		for(int i=0;i<m;i++){
			scanf("%d%d",&x,&y);
			x--;y--;
			printf("%d\n",query(x,y,1,0,n-1).result);
			
		}
	}
	
	return 0;	
}
