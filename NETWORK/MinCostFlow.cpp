/*
  oo = infinity value
  k = if flow >= k stop the algorithm (oo usually)
  n = number of nodes in the residual network
  edges = graph saved in edges list
  cost and capacity global arrays
*/
//Complexity O(n*n*m*m)
struct Edge{
	int from, to, capacity, cost;
};
void spfa(int s, int n, vector<int>& distance, vector<int>& parent) {
	distance.assign(n, oo);
	parent.assign(n, -1);
	vector<bool> inq(n, 0);
	distance[s] = 0, inq[s] = 1;
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for(int v : graph[u]) {
			if(capacity[u][v] > 0 && distance[v] > distance[u] + cost[u][v]) {
				distance[v] = distance[u] + cost[u][v];
				parent[v] = u;
				if(!inq[v]) {
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
}
int mincostflow(int n, vector<Edge>& edges, int K, int s, int t) {
	for(auto e : edges) {
		int u = e.from, v = e.to, w = e.capacity, c = e.cost;
		graph[u].push_back(v), graph[v].push_back(u);
		capacity[u][v] = w, capacity[v][u] = 0;
		cost[u][v] = c, cost[v][u] = -c;
	}
	int flow = 0, cost = 0;
	vector <int> distance, parent;
	while(flow < K) {
		spfa(s, n, distance, parent);
		if(distance[t] == oo) break;
		int f = K - flow, cur = t;
		while (cur != s) {
			f = min(f, capacity[parent[cur]][cur]);
			cur = parent[cur];
		}
		flow += f;
		cost += f * distance[t];
		cur = t;
		while(cur != s) {
			capacity[parent[cur]][cur] -= f;
			capacity[cur][parent[cur]] += f;
			cur = parent[cur];
		}
	}
	return cost;
}
