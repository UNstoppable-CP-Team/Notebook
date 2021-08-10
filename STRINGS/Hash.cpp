const ll mod = 1e9 + 7;
ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }
ll sub(ll a, ll b) { return a >= b ? a - b : a - b + mod; }
ll mul(ll a, ll b) { return a * b % mod; }
struct Hash{
	vector <ll> h, pw;
	int n; ll p;
	Hash(string &s, ll p) : p(p){
		n = s.size();
		h.assign(n, 0);
		pw.assign(n, 0);
		ll b = 1;
		for (int i = n - 1; i >= 0; --i, b = mul(b, p)) {
			h[i] = mul(s[i] - 'a', b);
			if (i + 1 < n) h[i] = add(h[i], h[i + 1]);
			pw[n - i - 1] = b;
		}
	}
	ll query(int l, int r) { return mul(pw[l], sub(h[l], r + 1 < n ? h[r + 1] : 0)); }
};
