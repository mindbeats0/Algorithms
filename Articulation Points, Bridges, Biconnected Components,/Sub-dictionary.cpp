#include <bits/stdc++.h>
using namespace std;

map<string,int>mp;
map<int,string>Tmp;
char buff[3000],dic[50],def[50];
vector<int>adj[110];
vector<int>Tadj[110];
int Rank(string str){
	if(mp.find(str)==mp.end()){
		int rnk=mp.size();
		mp[str]=rnk;
		Tmp[rnk]=str;
		return rnk;
	}
	else return mp[str];
}
vector<int>topSort;
bool vis[110];
void dfs(int node){
	if(vis[node])return ;
	vis[node]=true;
	
	
	for(int i=0;i<adj[node].size();i++)dfs(adj[node][i]);
	topSort.push_back(node);
}

int comp_counter,comp[110],out[110];
vector<int>nodes[110];
void dfs2(int node){
	if(vis[node])return ;
	vis[node]=true;
	
	comp[node]=comp_counter;
	nodes[comp_counter].push_back(node);
	//printf("!!!!!! %s %d\n",Tmp[node].c_str(),comp_counter);

	for(int i=0;i<Tadj[node].size();i++){
		//printf("~~~~~~~~  %s %s\n",Tmp[node].c_str(),Tmp[Tadj[node][i]].c_str());
		dfs2(Tadj[node][i]);
	}
}
void read(){
	for(int i=0;;i++){
		scanf("%c",&buff[i]);
		if(buff[i]=='\n'){
			buff[i]='\0';
			return ;
		}
	}
}
vector<string>res;
void dfs_asnwer(int node){
   if(vis[node])return ;
   vis[node]=true;
   
   res.push_back(Tmp[node]);
   for(int i=0;i<adj[node].size();i++)dfs_answer(adj[node][i]);
}
int main(){
	int n;

	while(scanf("%d",&n),n){
		assert(n>1);
		mp.clear();
		Tmp.clear();
		for(int i=0;i<n;i++)adj[i].clear(),Tadj[i].clear();
		
		
		gets(buff);
                 assert(buff[0]=='\0');

		for(int i=0;i<n;i++){
			gets(buff);
             //read();
             //  printf("-- %s\n",buff);

			sscanf(buff,"%s",dic);	
			Rank(dic);
			int offset=strlen(dic)+1;
                      
			while(offset<strlen(buff)){
				sscanf(buff+offset,"%s",def);
				adj[Rank(dic)].push_back(Rank(def));
				//printf("$$$   %s %s\n",dic,def);
				Tadj[Rank(def)].push_back(Rank(dic));
				offset+=strlen(def)+1;
			}
                       assert(adj[Rank(dic)].size());
		}
	   
               
		topSort.clear();
		memset(vis,0,sizeof vis);
		for(int i=0;i<mp.size();i++)if(!vis[i])dfs(i);
		
		
		memset(vis,0,sizeof vis);
		comp_counter=0;
		for(int i=topSort.size()-1;i>=0;i--)if(!vis[topSort[i]]){
		//	printf("**** %d\n",comp_counter);
			nodes[comp_counter].clear();
			dfs2(topSort[i]);
			comp_counter++;
		}
	     	
	    	
               res.clear(); 
               memset(vis,0,sizeof vis);
	       for(int i=0;i<comp_counter;i++){
			if(nodes[i].size()>1){
                                dfs_answer(nodes[i][0]);
				//for(int j=0;j<nodes[i].size();j++)res.push_back(Tmp[nodes[i][j]]);
			}
		}	
		sort(res.begin(),res.end());
		printf("%d\n",res.size());
		for(int i=0;i<res.size();i++){
			if(i)printf(" ");
			printf("%s",res[i].c_str());
		}
		printf("\n");
		
	}
	
	return 0;
}
