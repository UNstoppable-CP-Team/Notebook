template<class T> T calc(const T& a, const T& b) {
	return a ^ b; // can be any valid operation;
}
template <class T> struct HLD {

	vector < vector <int> > tree;
	vector <int> par, depth, in, out;
	vector <int> heavy, head;;

	SegmentTree <T>* seg;

	int cp, n;
	T NEUTER = 0; // set neuter value

	HLD (int n) : n(n) {
		tree.assign(n, {});
		par.assign(n, 0); depth.assign(n, 0);
		in.assign(n, 0); out.assign(n, 0);
		heavy.assign(n, -1); head.assign(n, 0);
		seg = new SegmentTree <T> (n);
	}

	void add_edge(int u, int v) { 
		tree[u].push_back(v); 
		tree[v].push_back(u);
	}

	int dfs(int u) {
		int len = 1, maxc = 0;
		for (auto &v : tree[u]) {
			if (v == par[u]) continue;
			par[v] = u; 
			depth[v] = depth[u] + 1;
			int cs = dfs(v);
			len += cs;
			if (cs > maxc) {
				maxc = cs; 
				heavy[u] = v;
			}
		}
		return len;
	}

	void dec(int u, int h) {
		head[u] = h; 
		in[u] = ++cp;
		if (heavy[u] != -1) dec(heavy[u], h);
		for (auto &v : tree[u]) {
			if (v != par[u] && v != heavy[u]) dec(v, v);
		}
		out[u] = cp;
	}

	void init() {
		cp = -1;
		dfs(0);
		dec(0, 0);
	}
	
	void update_subtree(int u, T& x) { 
		seg->update(in[u], out[u], x); 
	}
	T query_subtree(int u) {
		return seg->get(in[u], out[u]);
	}

	void update_path(int u, int v, T& x) {
		for (; head[u] != head[v]; v = par[head[v]]) {
			if (depth[head[u]] > depth[head[v]]) {
				swap(u, v);
			}
			seg->update(in[head[v]], in[v], x);
		}
		if (depth[u] > depth[v]) {
			swap(u, v);
		}
		seg->update(in[u], in[v], x);
	}

	T query_path(int u, int v) {
		T ans = NEUTER;
		for (; head[u] != head[v]; v = par[head[v]]) {
			if (depth[head[u]] > depth[head[v]]) {
				swap(u, v);
			}
			ans = calc(ans, seg->get(in[head[v]], in[v]));
		}
		if (depth[u] > depth[v]) {
			swap(u, v);
		}
		ans = calc(ans, seg->get(in[u], in[v]));
		return ans;
	}
};
