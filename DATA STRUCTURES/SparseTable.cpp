template <class T> struct Stable {
	int n, log2;
	vector <int> lg;
	vector <vector <T>> st;
	vector <T> a;
	Stable(vector <T> &a) : a(a) {
	//Stable (int n) : n(n) {
		n = a.size();
		lg.resize(n + 1, 0);
		for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
		log2 = lg[n];
		st.assign(n, vector <T> (log2 + 1, 0));
		for (int i = 0; i < n; ++i) st[i][0] = a[i];
		for (int j = 1; j <= log2; ++j) {
			for (int i = 0; i + (1 << j) <= n; ++i) {
				st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	T merge(T x, T y) { return a[x] >= a[y] ? x : y; }
	T get(int l, int r) {
		int j = lg[r - l + 1];
		return merge(st[l][j], st[r - (1 << j) + 1][j]);
	}
};
