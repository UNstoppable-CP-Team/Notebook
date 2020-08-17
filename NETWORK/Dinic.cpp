/*
*   edge: edge structure where
*         v = from, inv = id of the inverse edge, cap = capacity, flow = current flow on the edge.
*
*   Dinic: n = number of nodes, s = source node, t = sink node;
*          level = vector level of nodes (level network)
*          graph = network flow graph
*          call maxflow with oo = the require flow (infinite for maximum flow or a value if you want a flow <= x)
*
*/
//Complexity O (n * n * m); where m = number of edges
struct Edge {
	int v, inv, cap, flow;
	Edge(int v, int inv, int cap, int flow) : v(v), inv(inv), cap(cap), flow(flow) {}
};
struct Dinic {
	int n, s, t;
	vector <int> level;
	vector < vector <Edge> > graph;
	Dinic(int n, int s, int t) : n(n), s(s), t(t) {
		graph.assign(n, vector <Edge> ());
		level.resize(n);
	}
	void addedge(int u, int v, int cap) {
		graph[u].push_back(Edge(v, graph[v].size(), cap, 0));
		graph[v].push_back(Edge(u, graph[u].size() - 1, 0, 0));
	}
	bool bfs() {
		fill(level.begin(), level.end(), -1);
		queue <int> q;
		q.push(s);
		level[s] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for(int i = 0; i < graph[u].size(); ++i) {
				Edge &e = graph[u][i];
				if(e.flow < e.cap && level[e.v] == -1) {
					level[e.v] = level[u] + 1;
					q.push(e.v);
				}
			}
		}
		return level[t] != -1;
	}
	int dfs(int u, int pushed) {
		if(u == t) return pushed;
		int ans = 0;
		for(int i = 0; i < graph[u].size(); ++i) {
			Edge &e = graph[u][i];
			if(e.cap <= e.flow || level[e.v] != level[u] + 1) continue;
			int newflow = dfs(e.v, min(pushed, e.cap - e.flow));
			if(newflow <= 0) continue;
			e.flow += newflow;
			graph[e.v][e.inv].flow -= newflow;
			return newflow;
		}
		return 0;
	}
	int maxflow() {
		int ans = 0;
		while(bfs()) {
			while(int newflow = dfs(s, oo)) ans += newflow;
		}
		return ans;
	}
};
