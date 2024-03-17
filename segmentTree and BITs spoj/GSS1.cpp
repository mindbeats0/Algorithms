#include<cstdio>
#include<algorithm>
using namespace std;
struct node{int sum,left,right,maxi;};
int arr[500000];
node Tree[200000];
void build(int s,int e,int ind){
	if(s==e){
		Tree[ind].maxi=arr[s];
		Tree[ind].left=arr[s];
		Tree[ind].right=arr[s];
		Tree[ind].sum=arr[s];
		return ;
	}
	build(s,(s+e)/2,ind*2);
	build((s+e)/2+1,e,ind*2+1);
	
	Tree[ind].left=max(Tree[ind*2].left,Tree[ind*2].sum+Tree[ind*2+1].left);
	Tree[ind].right=max(Tree[ind*2+1].right,Tree[ind*2].right+Tree[ind*2+1].sum);
	Tree[ind].maxi=max(max(Tree[ind*2].maxi,Tree[ind*2+1].maxi),Tree[ind*2].right+Tree[ind*2+1].left);
	Tree[ind].sum=Tree[ind*2].sum+Tree[ind*2+1].sum;
	return ;
}
node ret;
bool flag;
void solve(int ws,int we,int curs,int cure,int ind){
	if(ws>cure || we<curs)return ;
	else if(ws<=curs && cure<=we){
		if(!flag){
			flag=1;
			ret.sum=Tree[ind].sum;
			ret.left=Tree[ind].left;
			ret.right=Tree[ind].right;
			ret.maxi=Tree[ind].maxi;
		}
		else{
			
			ret.maxi=max(max(ret.maxi,Tree[ind].maxi),ret.right+Tree[ind].left);
			ret.left=max(ret.left,ret.sum+Tree[ind].left);
			ret.right=max(Tree[ind].right,Tree[ind].sum+ret.right); 
			ret.sum=ret.sum+Tree[ind].sum;
		}
	}
	else{
		solve(ws,we,curs,(curs+cure)/2,ind*2);
		solve(ws,we,(curs+cure)/2+1,cure,ind*2+1);
	}
	return ;
}
int main(){
	int N,M,x,y;
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d",&arr[i]);
	build(0,N-1,1);
	scanf("%d",&M);
	for(int i=0;i<M;i++){
		scanf("%d%d",&x,&y);
		x--; y--;	
		flag=0;
		solve(x,y,0,N-1,1);
		printf("%d\n",ret.maxi);
	}
	return 0;
}
