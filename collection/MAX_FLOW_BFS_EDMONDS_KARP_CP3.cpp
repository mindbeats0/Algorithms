 //O(VE^2) (actually O(V^3E) Edmonds Karp's algorithm
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> vi;

#define MAX_V 40 // enough for sample graph in Figure 4.21/4.22/4.23/UVa 259
#define INF 1000000000

int res[MAX_V][MAX_V], mf, f, s, t;                          // global variables
vi p;

void augment(int v, int minEdge) {     // traverse BFS spanning tree from t to s
  if (v == s){
	   f = minEdge;  // record minEdge in a global variable f
	   return; 
   }  
  else if (p[v] != -1){
	   augment(p[v], min(minEdge, res[p[v]][v])); 
       res[p[v]][v] -= f; 
       res[v][p[v]] += f; 
   }  
}

int main() {
	int V, k, vertex, weight;
	scanf("%d %d %d", &V, &s, &t);
	memset(res, 0, sizeof res);
	for (int i = 0; i < V; i++) {
		scanf("%d", &k);
		for (int j = 0; j < k; j++) {
			scanf("%d %d", &vertex, &weight);
			res[i][vertex] = weight;
		}
	}

	mf = 0;                   // mf stands for max_flow
	while (1) {              // LOOP UP TO VE 
		f = 0;
		// run BFS
		vi dist(MAX_V, INF); dist[s] = 0; queue<int> q; q.push(s);
		p.assign(MAX_V, -1);           // record the BFS spanning tree, from s to t!
		while (!q.empty()){
		
			  int u = q.front(); q.pop();
			  if (u == t) break;      // immediately stop BFS if we already reach sink t
			  
			  for (int v = 0; v < MAX_V; v++)                 // note: this part is slow
					if (res[u][v] > 0 && dist[v] == INF)
						dist[v] = dist[u] + 1, q.push(v), p[v] = u;
					
		}
		
		augment(t, INF);     // find the min edge weight `f' along this path, if any
		if (f == 0) break;      // we cannot send any more flow (`f' = 0), terminate
		mf += f;                 // we can still send a flow, increase the max flow!
	}
	printf("%d\n", mf);                              // this is the max flow value
	return 0;
}
/*
  // Graph in Figure 4.21
  4 0 1
  2 2 70 3 30
  2 2 25 3 70
  3 0 70 3 5 1 25
  3 0 30 2 5 1 70
  // Graph in Figure 4.22
  4 0 3
  2 1 100 3 100
  2 2 1 3 100
  1 3 100
  0
  // Graph in Figure 4.23.A
  5 1 0
  0
  2 2 100 3 50
  3 3 50 4 50 0 50
  1 4 100
  1 0 125
  // Graph in Figure 4.23.B
  5 1 0
  0
  2 2 100 3 50
  3 3 50 4 50 0 50
  1 4 100
  1 0 75
  // Graph in Figure 4.23.C
  5 1 0
  0
  2 2 100 3 50
  2 4 5 0 5
  1 4 100
  1 0 125
  */
