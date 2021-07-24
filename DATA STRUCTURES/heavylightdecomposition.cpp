int op(int a, int b) { return a ^ b; } // sum, max, min, ...
struct HLD {
	//Segment tree seg;
	vector <vector<int>>  tree;
	vector <int> par, depth, heavy, head, pos;
	int cp, n;
	HLD (int n) : n(n) { 
		tree.assign(n, vector <int> ()); 
		seg.tree.assign(2 * n + 10, 0);
		seg.n = n;
	}
	void addedge(int u, int v) { 
		tree[u].push_back(v); 
		tree[v].push_back(u);
	}
	int dfs(int u) {
		int len = 1, maxc = 0;
		for (auto &v : tree[u]) {
			if (v == par[u]) continue;
			par[v] = u, depth[v] = depth[u] + 1;
			int cs = dfs(v);
			len += cs;
			if (cs > maxc) maxc = cs, heavy[u] = v;
		}
		return len;
	}
	void dec(int u, int h) {
		head[u] = h, pos[u] = cp++;
		if (heavy[u] != -1) dec(heavy[u], h);
		for (auto &v : tree[u]) {
			if (v != par[u] && v != heavy[u]) dec(v, v);
		}
	}
	void init() {
		par.assign(n, 0); 
		depth.assign(n, 0); 
		heavy.assign(n, -1);
		head.assign(n, 0);
		pos.assign(n, 0);
		cp = 0;
		dfs(0); dec(0, 0);
	}
	void update(int u, int x) { seg.update(pos[u], x); }
	int query(int u, int v) {
		int ans = 0; //set to a newter value
		for (; head[u] != head[v]; v = par[head[v]]) {
			if (depth[head[u]] > depth[head[v]]) swap(u, v);
			ans = op(ans, seg.query(pos[head[v]], pos[v]));
		}
		if (depth[u] > depth[v]) swap(u, v);
		ans = op(ans, seg.query(pos[u], pos[v]));
		return ans;
	}
};
