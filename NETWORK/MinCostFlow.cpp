/*
  oo = infinity value
  k = Given K find the the minimum cost of a flow = k
      for maximum flow - minimum cost use k = oo, and comment line "if (flow < k) return -1; "
  n = number of nodes in the residual network
  edges = graph saved in edges list
  cost and capacity global arrays
*/
//Complexity O(n*n*m*m)
template<class T> struct MCF{
	struct Edge {
	  int to, rev; T f, cap, cost;
	  Edge(int to, int rev, T cap, T cost, T f = 0) : to(to), rev(rev), cap(cap), cost(cost), f(f) {}
	};
	int n;
	vector<vector<Edge>> g;
	void addedge(int s, int t, T cap, T cost){
		g[s].push_back(Edge(t, g[t].size() , cap, cost));
		g[t].push_back(Edge(s, g[s].size() -1, 0, -cost));
	}
	MCF (int n) :n(n) { g.resize(n); }
	void spfa(int v0, vector<T>& d, vector<int>& p) {
		d.assign(n, oo); d[v0] = 0;
		vector<bool> inq(n,0);
		queue<int> q;
		q.push(v0);
		p.assign(n,-1);
		while (!q.empty()) {
		  int u = q.front();
		  q.pop();
		  inq[u] = 0;
			for(int i= 0; i< g[u].size(); ++i){
				Edge v = g[u][i];
				if (v.cap - v.f > 0 && d[v.to] > d[u] + v.cost ) {
					d[v.to] = d[u] + v.cost;
					p[v.to] = v.rev;
					if (!inq[v.to]) {
						inq[v.to] = 1;
						q.push(v.to);
					}
				}
			}
		}
	}
	T mincostflow(ll K, int s, int t) {
		T flow = 0, cost = 0;
		vector<int> p;
		vector<ll> d;
		while (flow < K) {
			spfa(s, d, p);
			if (d[t] == oo) break;
			//find max flow on that path
			T f = K - flow;
			int cur = t;
			while (cur != s) {
				int u = g[cur][p[cur]].to;
				int rev = g[cur][p[cur]].rev;
				T c = g[u][rev].cap - g[u][rev].f;
				f = min(f, c);
				cur = u;
			}
			//apply flow
			flow += f;
			cost += f * d[t];
			cur = t;
			while (cur != s) {
				int rev = g[cur][p[cur]].rev;
				int u = g[cur][p[cur]].to;
				g[u][rev].f += f;
				g[cur][p[cur]].f -= f;
				cur = u;
			}
		}
		if(flow< K) return -1;
		return cost;
	}
};
