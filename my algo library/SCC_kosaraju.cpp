struct SCC{

    stack<int>S;
    bool vis[3*N+5];
    int ID[3*N+5];
    int id;
    SCC(){
        while(!S.empty())S.pop();
        memset(vis,0,sizeof vis);
        memset(ID,-1,sizeof ID);
        id=0;
    }
    void dfs(int u,int pass){
        vis[u]=true;

        if(pass){
            ID[u]=id;
            if(VALUE[id].first==-1)VALUE[id]=value[u];
            else VALUE[id]=min(value[u],VALUE[id]);

        }
        for(int edge=head[pass][u];edge!=-1;edge=nxt[pass][edge]){
             int v=to[pass][edge];
            if(!vis[v])dfs(v,pass);
        }
        S.push(u);

    }
}scc;



int main(){

    // SCC : kosaraju's Algorithm
    for(int i=0;i<rnkID;i++)if(!scc.vis[i])scc.dfs(i,0);

    memset(scc.vis,0,sizeof scc.vis);
    while(!scc.S.empty()){
        int v=scc.S.top();
        if(!scc.vis[v])scc.dfs(v,1),scc.id++;
        scc.S.pop();
    }

}
