/*
  oo = infinity value
  k = Given K find the the minimum cost of a flow = k
      for maximum flow - minimum cost use k = oo, and comment line "if (flow < k) return -1; "
  n = number of nodes in the residual network
  edges = graph saved in edges list
  cost and capacity global arrays
*/
//Complexity O(n*n*m*m)
struct Edge{
	int from, to, cap, cost;
};
struct MCF{
	int n, s, t;
	vector< vector <int> > graph, capacity, cost;
	MCF (int n, int s, int t) : n(n), s(s), t(t), graph(n) {
		capacity.assign(n, vector <int> (n));
		cost.assign(n, vector <int> (n));
	}
	void addedge(int u, int v, int cap, int c) {
		graph[u].push_back(v), graph[v].push_back(u);
		capacity[u][v] = cap, capacity[v][u] = 0;
		cost[u][v] = c, cost[v][u] = -c;
	}
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
	int mincostflow(int K) {
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
		if(flow < K) return -1;
		return cost;
	}
};
