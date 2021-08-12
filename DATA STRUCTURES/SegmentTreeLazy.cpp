template <class T> struct Stree {
	T neut = 0; //set neuter value
	int n; 
	vector <T> tree; 
	vector <bool> lazy;
	Stree (int n) : n(n) {
		tree.assign((n + 1) << 2, neut);
		lazy.assign((n + 1) << 2, 0);
	}
	int left(int u) { return u << 1; } 
	int right(int u) { return u << 1 | 1; }
	T merge(T a, T b) { return 0; } // set merge operation
	void propagate(int u, int tl, int tr) {
		if (!lazy[u]) return;
		if (tl != tr) { //seg lazy operation
		}
		lazy[u] = 0;
	}
	void update(int u, int tl, int tr, int l, int r, T val) {
		if (l > r) return;
		if (tl == l && tr == r) {
			//tree[u] = ;
			lazy[u] = 1;
		} else {
			propagate(u, tl, tr);
			int tm = (tl + tr) >> 1;
			update(left(u), tl, tm, l, min(tm, r), val);
			update(right(u), tm + 1, tr, max(l, tm + 1), r, val);
			tree[u] = merge(tree[left(u)], tree[right(u)]);
		}
	}
	T query(int u, int tl, int tr, int l, int r) {
		if (l > r) return neut;
		if (tl == l && tr == r) return tree[u];
		int tm = (tl + tr) >> 1;
		propagate(u, tl, tr);
		return merge(query(left(u), tl, tm, l, min(tm, r)), query(right(u), tm + 1, tr, max(l, tm + 1), r));
	}
	void update(int l, int r, T val) { update(1, 0, n - 1, l, r, val); }
	T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
