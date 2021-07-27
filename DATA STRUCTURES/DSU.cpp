struct DSU {
	int n, comp = n;
	vector <int> f, len;
	DSU (int n) : n(n) {
		f.assign(n + 10, 0); iota(f.begin(), f.end(), 0);
		len.assign(n + 10, 1);
	}
	int find(int n) { return f[n] = f[n] == n ? n : find(f[n]); }
	void merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (len[a] < len[b]) swap(a, b);
		len[a] += len[b];
		f[b] = a;
		comp--;
	}
};
