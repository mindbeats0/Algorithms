#include <bits/stdc++.h>
using namespace std;
#define all(v) ((v).begin()),((v).end())
const int MAXN=1e5;
const int MAXM=1e3;
const int MAXA='z'+1;

char s[MAXN+5],pat[MAXM+5][MAXM+5];
int k;
int nodeCounter;
struct node{
	int id;
	
	node*child[MAXA];
	vector<char>chars;
	
	node*fail;
	vector<int>patIdx;
	
	node (){
		memset(child,0,sizeof child);
		id = nodeCounter++;
	}
	
	~node (){
		memset(child,0,sizeof child);
		id = nodeCounter++;
	}
	
	void insert(char* s,int idx){ // insert the pattern 'idx' in the trie
		if(!*s){
			patIdx.push_back(idx);
		}
		else{
			if(!child[*s]){
				child[*s] = new node();
				chars.push_back(*s);
			}
			child[*s]->insert(s+1,idx);
		}	
	}
	
	void clr(){
		for(int ch='A';ch<='z';ch++){
			if(child[ch]){
				child[ch]->clr();
				delete child[ch];
			}
		}
		
	}
};
// get next node when i want to move from the given ptr through edge "ch"
void move(node*&ptr,int ch){
	while(ptr->id && !ptr->child[ch])
		ptr = ptr->fail;
		
	if(ptr->child[ch])
		ptr = ptr->child[ch];
	 
}
node* buildAhoTree(){
	node*root=new node();
	
	// buid trie
	for(int i=0;i<k;i++)
		root->insert(pat[i],i);
	
	// build transitions edges
	queue<node*>q;
	for(int ch='A';ch<='z';ch++){
		if(!root->child[ch])continue;
		
		root->child[ch]->fail=root;
		q.push(root->child[ch]);
	}
	
	node*cur;
	while(!q.empty()){
		cur=q.front();
		q.pop();
		
		for(int ch='A';ch<='z';ch++){
			if(!cur->child[ch])continue;
			
			node*ptr=cur->fail;
		    move(ptr,ch);
		    cur->child[ch]->fail=ptr;
		    cur->child[ch]->patIdx.insert(cur->child[ch]->patIdx.end() , all(ptr->patIdx) );
		    
            q.push(cur->child[ch]);	
		}	
	}
	return root;
}
void match(char *s,node*root,vector<bool>&res){
	node*ptr = root;
	for(int i=0;s[i];i++){
		move(ptr,s[i]);
		
		for(int j=0;j< ptr->patIdx.size();j++)
			res[ptr->patIdx[j]]=true;
		
	}
}
int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%s%d",s,&k);
		for(int i=0;i<k;i++)
			scanf("%s",pat[i]);
		
		nodeCounter=0;
		node*root = buildAhoTree();
		
		
		vector<bool > res(k);
		match(s,root,res);  
   		
   		for(int i=0;i<k;i++)printf("%c\n",res[i]?'y':'n');
   		
   		root->clr();
   		delete root;
	}
}
