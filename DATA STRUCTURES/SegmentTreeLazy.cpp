template <class T> struct SegmentTree {
	T neut = 0; //set neuter value
	int n; 
	vector <T> tree, sum; 
	vector <bool> lazy;
	SegmentTree (int n) : n(n) {
		tree.assign((n + 1) << 2, neut);
		sum.assign((n + 1) << 2, neut);
		lazy.assign((n + 1) << 2, 0);
	}
	int left(int u) { return u << 1; } 
	int right(int u) { return u << 1 | 1; }
	T merge(T a, T b) { return a + b; } // set merge operation
	void propagate(int u, int tl, int tr) {
		if (!lazy[u]) return;
		tree[u] += sum[u] * (tr - tl + 1);
		if (tl != tr) { //seg lazy operation
			sum[left(u)] += sum[u];
			sum[right(u)] += sum[u];
			lazy[left(u)] = lazy[right(u)] = 1;
		}
		lazy[u] = sum[u] = 0;
	}
	void update(int u, int tl, int tr, int l, int r, T val) {
		propagate(u, tl, tr);
		if (tr < l || r < tl) return;
		if (l <= tl && tr <= r) {
			sum[u] += val;
			lazy[u] = 1;
			propagate(u, tl, tr);
		} else {
			int tm = (tl + tr) >> 1;
			update(left(u), tl, tm, l, r, val);
			update(right(u), tm + 1, tr, l, r, val);
			tree[u] = merge(tree[left(u)], tree[right(u)]);
		}
	}
	T query(int u, int tl, int tr, int l, int r) {
		if (tr < l || r < tl) return neut;
		propagate(u, tl, tr);
		if (l <= tl && tr <= r) return tree[u];
		int tm = (tl + tr) >> 1;
		return merge(query(left(u), tl, tm, l, r), query(right(u), tm + 1, tr, l, r));
	}
	void update(int l, int r, T val) { update(1, 0, n - 1, l, r, val); }
	T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
