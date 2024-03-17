#include <bits/stdc++.h>
using namespace std;
const int MAXN=1500;
const int MAXA=26;
char T[MAXN+5],buff[MAXN+5];
int bad[MAXN+5];

struct node{
	node* child[MAXA];
	int count;
	
	node(){}
	node(int count){
		memset(child,0,sizeof child);
		this->count=count;
	}
	void insert(char*s){
		if(!(*s)){
			return;
		}
		else{
			if(!child[(*s)-'a'])
				child[(*s)-'a'] = new node(count+bad[(*s)-'a']);
			child[(*s)-'a']->insert(s+1);
		}
	}
};

int solve(node*ptr,int k){
	
	int ret=0;
	if(ptr->count<=k)ret++;
	
	for(int i=0;i<26;i++)
		if(ptr->child[i])
			ret += solve(ptr->child[i],k);
	
	return ret;
}
int main(){
	int k;
	scanf("%s%s%d",T,buff,&k);
	for(int i=0;i<strlen(buff);i++)bad[i]=((buff[i]-'0')+1)%2;
	
	node*root = new node(0);
	for(int i=0;i<strlen(T);i++)
		root->insert(T+i);
	printf("%d\n",solve(root,k)-1);
	
}
