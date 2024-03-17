#include <bits/stdc++.h>
using namespace std;

vector<int>adj[2005];
bool vis[2005];
int color[2005];
bool isbipartite( int s){
memset(color,-1,sizeof color);
    queue<int>q;
    q.push(s);
    color[s]=0;
    bool bipartite=true;

    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=1;

        for(int i=0;i<(int)adj[u].size();i++){

             int v=adj[u][i];
             if(color[v]==-1){
                  color[v]=1-color[u];
                  q.push(v);
             }
            else if(color[v]==color[u]){
                bipartite=false;
            }
        }


    }
    return bipartite;
}
int main(){
    int T,n,m;
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>n>>m;
    for(int i=0;i<n;i++)adj[i].clear();
        for(int i=0;i<m;i++){
            int a,b;
            cin>>a>>b;
            a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }



        memset(vis,0,sizeof vis);

        bool flag=1;
        for(int i=0;i<n;i++){
            if(!vis[i])flag&=isbipartite(i);
            if(!flag)break;
        }

        cout<<"Scenario #"<<t<<":\n";
        if(flag)cout<<"No suspicious bugs found!\n";
        else{
            cout<<"Suspicious bugs found!\n";
        }
    }
}
