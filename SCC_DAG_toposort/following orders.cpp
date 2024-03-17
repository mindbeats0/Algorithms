#include <bits/stdc++.h>
using namespace std;
char line1[100],line2[300];
vector<int>adj[30];
int in[30];
bool taken[30];
vector<int>all;
char op[30];
void solve(int idx){
	if(idx == all.size()){
		op[idx]='\0';
		printf("%s\n",op);
		return ;
	}
	
	for(int i=0;i<all.size();i++){
		
		int cur=all[i];
		if(!in[cur] && !taken[cur]){
			for(int j=0;j<adj[cur].size();j++)in[adj[cur][j]]--;taken[cur]=1;
			op[idx]=cur+'a',solve(idx+1);
			for(int j=0;j<adj[cur].size();j++)in[adj[cur][j]]++;taken[cur]=0;
		}
	}
}
int main(){
	int tt=0;
    while(gets(line1)){
        gets(line2);
        
		all.clear();    
		memset(in,0,sizeof in);
		memset(taken,0,sizeof taken);
		for(int i=0;i<30;i++)adj[i].clear();
		
		for(int i=0;i<strlen(line1);i+=2)
			all.push_back(line1[i]-'a');
		sort(all.begin(),all.end());
		
		for(int i=0;i<strlen(line2);i+=4){
			int a=line2[i]-'a';
			int b=line2[i+2]-'a';
			adj[a].push_back(b);
			in[b]++;
		}
		if(tt)printf("\n");
		solve(0);
		tt++;
	}
}
