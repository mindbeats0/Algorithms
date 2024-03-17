#include <bits/stdc++.h>
using namespace std;
const int MAXN=30000;
char word[MAXN+5],acc[MAXN+5];
int Tree[4*MAXN],Lazy[4*MAXN];
void build(int idx,int s,int e){
	Lazy[idx] = 0;
	if(s==e){
		Tree[idx] = acc[s];
		return ;
	}
	int mid = (s+e)/2;
	build(idx*2,s,mid);
	build(idx*2+1,mid+1,e);
 
	Tree[idx] = min(Tree[idx*2],Tree[idx*2+1]);
}
void relax(int idx,int s,int e){
	Tree[idx] += Lazy[idx];
	if(s!=e){
		Lazy[idx*2] += Lazy[idx];
		Lazy[idx*2+1] += Lazy[idx];
	}
	Lazy[idx] = 0 ;
}
void update(int idx,int s,int e,int qs,int qe,int val){
	relax(idx,s,e);
	if(s>qe || e<qs)return ;
	if(s>=qs && e<=qe){
		Lazy[idx] += val;
		relax(idx,s,e);
		return ;
	}
	int mid = (s+e)/2;
	update(idx*2,s,mid,qs,qe,val);
	update(idx*2+1,mid+1,e,qs,qe,val);
	Tree[idx] = min(Tree[idx*2],Tree[idx*2+1]);
}
 
int query(int idx,int s,int e,int qs,int qe){
	relax(idx,s,e);
 
	if(s>qe || e<qs)return 0 ;
	if(s>=qs && e<=qe){
		return Tree[idx];
	}
	int mid = (s+e)/2;
	return query(idx*2,s,mid,qs,qe)+query(idx*2+1,mid+1,e,qs,qe);
}
int main(){
	int n,m,k;
	for(int tt=1;tt<=10;tt++){
		scanf("%d%s",&n,word);
		for(int i=1;i<=n;i++){
			if(word[i-1]=='(')acc[i]=1;
			else acc[i]=-1;
			acc[i] += acc[i-1];
		}
        int all=acc[n];
		build(1,1,n);
		scanf("%d",&m);
 
		printf("Test %d:\n",tt);
		for(int i=0;i<m;i++){
			scanf("%d",&k);
			if(!k){
				if( !query(1,1,n,1,n) && !all)printf("YES\n");
				else printf("NO\n");
			}
			else{
				if(word[k-1]=='('){
					word[k-1]=')';
					update(1,1,n,k,n,-2);
                    all-=2;
				}
				else if(word[k-1]==')'){
					word[k-1]='(';
					update(1,1,n,k,n,2);
                    all+=2;
				}
 
			}
		}
	}
	return 0;
}
