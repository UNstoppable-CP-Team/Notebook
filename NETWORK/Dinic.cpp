/*
*   T = flow data type (sometimes it can be ll or int)
*   edge: edge structure where
*         v = from, cap = capacity, inv = id of the inverse edge, flow = current flow on the edge.
*
*   Dinic: n = number of nodes, s = source node, t = sink node;
*          lvl = vector level of nodes (level network)
*          g = network flow graph
*          call maxflow with oo = the require flow (infinite for maximum flow or a value if you want a flow <= x)
*
*/
//Complexity O (n * n * m); where m = number of edges
typedef int T;
struct Edge {
	int v, inv; 
	T cap, flow;
	Edge (int v, int inv, T cap, T flow) : v(v), inv(inv), cap(cap), flow(flow) {}
};
struct Dinic {
	int n, s, t;
	vector <int> lvl;
	vector < vector <Edge> > g;
	Dinic(int n, int s, int t) : n(n), s(s), t(t), lvl(n), g(n) {}
	void addedge(int u, int v, T cap) {
		g[u].push_back(Edge(v, g[v].size(), cap, 0));
		g[v].push_back(Edge(u, g[u].size() - 1, 0, cap));
	}
	bool bfs() {
		fill(lvl.begin(), lvl.end(), -1);
		queue <int> q;
		q.push(s);
		lvl[s] = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < g[u].size(); ++i) {
				Edge &e = g[u][i];
				if(e.cap > 0 && lvl[e.v] == -1) {
					lvl[e.v] = lvl[u] + 1;
					q.push(e.v);
				}
			}
		}
		return lvl[t] != -1;
	}
	T dfs(int u, T newflow) {
		if (u == t) return newflow;
		T ans = 0;
		for (int i = 0; i < g[u].size(); ++i) {
			Edge &e = g[u][i];
			if( e.cap <= 0 && lvl[e.v] != lvl[u] + 1) continue;
			T f = dfs(e.v, min(newflow, e.cap));
			if (f == 0) continue;
			ans += f;
			newflow -= f;
			e.cap -= f, e.flow += f;
			g[e.v][e.inv].cap += f, g[e.v][e.inv].flow -= f;
			if(newflow == 0) return ans;
		}
		if(!ans) lvl[u] = -1;
		return ans;
	}
	T flow() {
		T f = 0;
		while(bfs()) {
			f += dfs(s, oo);
		}
		return f;
	}
};
