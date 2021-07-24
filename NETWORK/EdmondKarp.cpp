/*	Graph = network flow
	oo = infinite number
	maxn = maximum number of nodes
 	Capacity is [maxn][maxn]
	Call ans = maxflow(s, t) int the main
*/
//Complexity O(n*m*m)
template <class T> struct Edkarp {
	int n, s, t;
	vector< vector<int> > graph; 
	vector <vector <T> > capacity;
	Edkarp(int n) : n(n) {
		graph.resize(n);
		capacity.assign(n, vector<T> (n, 0));
	}
	void addedge(int u, int v, T c) {
		graph[u].push_back(v), graph[v].push_back(u);
		capacity[u][v] = c, capacity[v][u] = 0;
	}
	T bfs(vector<int>& parent) {
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
					T newflow = min(flow, capacity[u][v]);
					if(v == t) return newflow;
					q.push({v, newflow});
				}
			}
		}
		return 0;
	}
	T maxflow(int u, int v) {
		s = u, t = v;
		T flow = 0, newflow;
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
};
