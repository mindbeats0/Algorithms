#define MAXN 700     		//maximum number of nodes
int cap[MAXN][MAXN]; 		//capacity
int n;						//number of nodes

int path[MAXN];
int pathLength;
bool visited[MAXN];

// Implement in anyway that get a path: DFS, BFS, Dijkstra...whatever
int getPath(int curNode,int TargetNode,int idx,int mincap){
	path[idx]=curNode;
	if (curNode==TargetNode){
		pathLength=idx+1;
		return mincap;
	}
	
	int ret = 0;
	visited[curNode]=true;
	
	for(int i=0;i<n;i++){		
		if (visited[i] || cap[curNode][i]<=0) continue;
		
		ret = getPath(i, TargetNode,curLen+1, min(mincap,cap[curNode][i]));
		
		if (ret>0) break;	// We found a path with flow
	}
	return ret;
}

int maxFlow(int src, int sink){
	int total_flow = 0;

	while(1){ // takes up to mf iteration
		memset(visited,0,sizeof(visited));
		int newflow=getPath(src,sink,0,INT_MAX);
		
		if (!newflow) break;	// once no more paths, STOP
		
		for(int i=1;i<pathLength;i++){
			int m=path[i-1],n=path[i];
			
			cap[m][n]-=newflow;
			cap[n][m]+=newflow;		// Add reversed edge
		}
		total_flow+=newflow;
	}
	
	return total_flow;
}
