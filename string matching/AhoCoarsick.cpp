#include<set>
#include<map>
#include<list>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<complex>
#include<sstream>
#include<bits/stdc++.h>
using namespace std;

#define all(v)				((v).begin()) , ((v).end())
#define sz(v)				((int)((v).size()))

const int MAXA =26;

char pats[100][100];
char s[100];
int nextNodeId = 0;

struct node {
	int id;
	
	node* child[MAXA];
	vector<char> chars;
	
	node* fail;
	vector<int> patIdx;	
	
	node() {
		memset(child, 0, sizeof child);
		id = nextNodeId++;
	}

	void insert(char* str, int idx) {

	    if (!*str) {
			patIdx.push_back(idx);
		} 
		else {
			if (!child[*str-'a']) {
				child[*str-'a'] = new node();
				chars.push_back(*str-'a');
			}
			child[*str-'a']->insert(str + 1, idx);
		}
	}
};

void move(node* &ptr, int ch) {
	// the root has all the 26 edges pointing to itself
	while (!ptr->child[ch])
		ptr = ptr->fail;
	ptr = ptr->child[ch];
}

node* buildAhoTree(char pat[][100], int k) {
	node * root = new node();

    // build the trie
    for(int i=0;i<k;i++)
		root->insert(pat[i], i);
	
	// build transitions edges
	queue<node*> q;
	for(int ch=0;ch<MAXA;++ch){
		if (root->child[ch]){
			q.push(root->child[ch]); 
			root->child[ch]->fail = root;
		}
		else
			root->child[ch] = root; //Sentinel
	}
	
	node* cur;
	while (!q.empty()) {
		cur = q.front();
		q.pop();

		for(int ch=0;ch<MAXA;ch++){
			if(!cur->child[ch])continue;
			q.push(cur->child[ch]);
			
			node* ptr = cur->fail;

			move(ptr, ch);// ptr sent by reference

			cur->child[ch]->fail = ptr;
			cur->child[ch]->patIdx.insert(cur->child[ch]->patIdx.end(), all(ptr->patIdx));
		}
	}
	return root;
}

void match(const char* str, node* root, vector<vector<int> > & res) {
	node* ptr = root;

	for (int i = 0; str[i]; i++) {
		move(ptr, str[i]-'a');
		for(int j=0;j < ptr->patIdx.size();j++)
			res[ptr->patIdx[j]].push_back(i);
	}
}

int main() {

    int k;
	scanf("%s%d",s,&k);
	for(int i=0;i<k;i++)
		scanf("%s", pats[i]);
	
	node* root = buildAhoTree(pats, k);
	
	
	// now throw the patterns in the trash, we have the String s and a trie
	// find all occurences of patterns in that string s
	vector<vector<int> > res(k);
	match(s, root, res);

	for(int i=0;i<k;i++) {
		if (sz(res[i]))
			printf("y\n");
		else
			printf("n\n");
	}

	return 0;
}
