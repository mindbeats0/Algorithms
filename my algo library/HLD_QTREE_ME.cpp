#include <bits/stdc++.h>
using namespace std;

const int N=10000;
const int LN=14;


int last;
int to[2*N+5],cost[2*N+5],nxt[2*N+5],head[N+5],input_edge[2*N+5],req_node[N+5];
void addEdge(int f,int t,int c,int i){
    input_edge[last]=i;

    to[last]=t;
    cost[last]=c;
    nxt[last]=head[f];
    head[f]=last;

    last++;
}

int depth[N+5],subsize[N+5],pa[LN+5][N+5];
void dfs(int node,int prev,int _depth){
    pa[0][node]=prev;
    depth[node]=_depth;
    subsize[node]=1;

    for(int edge=head[node];edge!=-1;edge=nxt[edge])if(to[edge]!=prev){
        int inputno=input_edge[edge];
        req_node[inputno]=to[edge];

        dfs(to[edge],node,_depth+1);
        subsize[node]+=subsize[to[edge]];
    }
    return ;
}


int chainNo,ptr;
int chainHead[N+5],chainOfNode[N+5],posOfNode[N+5],Array[N+5];
void HLD(int node,int prev,int _cost){
   if(chainHead[chainNo]==-1)chainHead[chainNo]=node;

   chainOfNode[node]=chainNo;
   posOfNode[node]=ptr;

   Array[ptr]=_cost;
   ptr++;


   int special_edge=-1;
   for(int edge=head[node];edge!=-1;edge=nxt[edge])if(to[edge]!=prev){
        if(special_edge==-1 || subsize[to[edge]]>subsize[to[special_edge]])special_edge=edge;
   }
   if(special_edge!=-1)HLD(to[special_edge],node,cost[special_edge]);

    for(int edge=head[node];edge!=-1;edge=nxt[edge])if(to[edge]!=prev){
        if(special_edge!=edge){
            chainNo++;
            HLD(to[edge],node,cost[edge]);
        }
   }

}

int Tree[4*N];
void make_tree(int ind,int s,int e){
    if(s==e)Tree[ind]=Array[s];
    else {
        make_tree(ind*2,s,(s+e)/2);
        make_tree(ind*2+1,(s+e)/2+1,e);
        Tree[ind]=max(Tree[ind*2],Tree[ind*2+1]);
    }
}

int IND,VAL;
void change(int ind,int s,int e){
    if(s>IND || e<IND)return ;
    if(s==e){Tree[ind]=Array[s]=VAL; return ;}

    change(ind*2,s,(s+e)/2);
    change(ind*2+1,(s+e)/2+1,e);
    Tree[ind]=max(Tree[ind*2],Tree[ind*2+1]);

}
int S,E;
int query(int ind,int s,int e){
    if(s>E || e<S)return 0;
    if(s>=S && e<=E)return Tree[ind];
    return max(query(ind*2,s,(s+e)/2) ,query(ind*2+1,(s+e)/2+1,e) );
}



int answer(int u,int v){
    int uchain,vchain=chainOfNode[v];
    int ret=0;

    while(1){
        uchain=chainOfNode[u];

        if(uchain==vchain){
            if(u==v)break;

            S=posOfNode[v]+1; E=posOfNode[u];
            ret=max(ret,query(1,0,ptr-1));
            break;
        }


        S=posOfNode[chainHead[uchain]]; E=posOfNode[u];
        ret=max(ret,query(1,0,ptr-1));
        u=chainHead[uchain];
        u=pa[0][u];

    }

    return ret;
}


int LCA(int u, int v){

    if(depth[u]<depth[v])swap(u,v);

    int len=depth[u]-depth[v];
    for(int i=0;i<LN;i++)if( (len>>i)&1 )u=pa[i][u];
    if(u==v)return u;

    for(int i=LN-1;i>=0;i--)
        if(pa[i][u]!=pa[i][v])
            u=pa[i][u],v=pa[i][v];

    return pa[0][u];

}
void init_ancestors(){
    for(int j=1;j<LN;j++)
        for(int i=0;i<N;i++)
            if(pa[j-1][i]!=-1)
                pa[j][i]=pa[j-1][pa[j-1][i]];
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
       int n,a,b,c;
       char str[100];
       scanf("%d",&n);

       last=0;
       memset(head,-1,sizeof head);

       for(int i=0;i<n-1;i++){
            scanf("%d%d%d",&a,&b,&c);
            a--; b--;
            addEdge(a,b,c,i);
            addEdge(b,a,c,i);
       }
       memset(pa,-1,sizeof pa);
       dfs(0,-1,0);


       chainNo=0;ptr=0;
       memset(chainHead,-1,sizeof chainHead);
       HLD(0,-1,-1);



       make_tree(1,0,ptr-1);
       init_ancestors();

        while(1){
           scanf("%s",str);
           if(str[0]=='Q'){
              scanf("%d%d",&a,&b);
              a--; b--;
              int lca=LCA(a,b);
              printf("%d\n",max( answer(a,lca) , answer(b,lca)));
           }
           else if(str[0]=='C'){
              //CHANGE i ti : change the cost of the i-th edge to ti
              scanf("%d%d",&a,&b); a--;
              int node=req_node[a];
              IND=posOfNode[node]; VAL=b;
              change(1,0,ptr-1);
           }
           else break;
        }

    }
    return 0;
}
