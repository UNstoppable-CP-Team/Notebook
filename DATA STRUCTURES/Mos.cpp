const int maxn = 1e5, rootn = 317;
struct Query {
	int l, r, i;
	Query(int l, int r, int i) : l(l), r(r), i(i) {}
	bool operator < ( const Query b) {
		if (l / rootn != b.l / rootn) return l / rootn < b.l / rootn;
		return r < b.r;
	}
};
struct Mos{ 
	int n, lo, hi, cur;
	vector <int> cnt, a;
	vector <Query> q;
	Mos (int n, int lo, int hi, int cur) : n(n), lo(lo), hi(hi), cur(cur) {
		cnt.assign(n + 10, 0);
		a.assign(n + 10, 0);
	}
	void add (int x) {
		cur -= cnt[x];
		cnt[x]++;
		cur += cnt[x];
	}
	void remove(int x) {
		cur -= cnt[x];
		cnt[x]--;
		cur += cnt[x];
	}
	void update(int l, int r) {
		while (hi < r) add(a[++hi]);
		while (lo > l) add(a[--lo]);
		while (hi > r) remove(a[hi--]);
		while (lo < l) remove(a[lo++]);
	}
};
