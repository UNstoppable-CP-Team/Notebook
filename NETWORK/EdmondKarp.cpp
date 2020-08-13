/*	Graph = network flow
	oo = infinite number
	maxn = maximum number of nodes
 	Capacity is [maxn][maxn]
	Call ans = maxflow(s, t) int the main
*/
//Complexity O(n*m*m)
int bfs(int s, int t, vector<int>& parent) {
	parent.assign(maxn, -1);
	parent[s] = -2;
	queue<pii> q;
	q.push({s, oo});
	while(!q.empty()) {
		int u = q.front().first, flow = q.front().second;
		q.pop();
		for(int v : graph[u]) {
			if(parent[v] == -1 && capacity[u][v]) {
				parent[v] = u;
				int newflow = min(flow, capacity[u][v]);
				if(v == t) return newflow;
				q.push({v, newflow});
			}
		}
	}
	return 0;
}
int maxflow(int s, int t) {
	int flow = 0, newflow;
	vector <int> parent;
	while(newflow = bfs(s, t, parent)) {
		flow += newflow;
		int cur = t;
		while(cur != s) {
			capacity[parent[cur]][cur] -= newflow;
			capacity[cur][parent[cur]] += newflow;
			cur = parent[cur];
		}
	}
	return flow;
}
