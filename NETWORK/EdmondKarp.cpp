/*	Graph = network flow
	oo = infinite number
	maxn = maximum number of nodes
 	Capacity is [maxn][maxn]
	Call ans = maxflow(s, t) int the main
*/
//Complexity O(n*m*m)
struct  Edkarp {
	int n, s, t;
	vector< vector<int> > graph, capacity;
	Edkarp(int n, int s, int t) : n(n), s(s), t(t) {
		graph.resize(n);
		capacity.assign(n, vector<int> (n, 0));
	}
	void addedge(int u, int v, int c) {
		graph[u].push_back(v), graph[v].push_back(u);
		capacity[u][v] = c, capacity[v][u] = 0;
	}
	int bfs(vector<int>& parent) {
		parent.assign(n, -1);
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
	int maxflow() {
		int flow = 0, newflow;
		vector <int> parent;
		while(newflow = bfs(parent)) {
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
}
