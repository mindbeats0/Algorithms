#include<bits/stdc++.h>
using namespace std;

#define SET(a) memset(a,-1,sizeof(a))
#define CLR(a) memset(a,0,sizeof(a))
#define PI acos(-1.0)

#define MOD 1000000007
#define MX 1010


int vis[MX];
vector<int>adj[MX];
int t, dis[MX], low[MX], parent[MX], road[MX][MX];

void findBridge(int u)
{
    low[u] = dis[u] = ++t;
    vis[u]=true;
    for(int i=0;i<adj[u].size();i++)
    {
        int v=adj[u][i];
        if(!vis[v])
        {
            parent[v]=u;
            findBridge(v);
            low[u]=min(low[u], low[v]);
            if(low[v]>dis[u])   
                 road[u][v]=road[v][u]=1;
	   else road[u][v]=1;
        }
        else if(dis[v]<dis[u]&& parent[u]!=v) // back edge but not direct parent 
        {
            low[u]=min(low[u], dis[v]);
	     road[u][v]=1;
        }

    }
return;
}


int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n, m, u, v, kk=1;
    while(cin>>n>>m && n)
    {
        for(int i=0;i<m;i++)
        {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        t=0;
        
        findBridge(1);

        cout<<kk++<<"\n\n";
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(road[i][j])
                    cout<<i<<" "<<j<<'\n';
        cout<<"#\n";

        CLR(road);
        CLR(vis);
        CLR(parent);
        for(int i=1;i<=n;i++)
            adj[i].clear();
    }
return 0;
}
