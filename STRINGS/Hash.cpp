template<class T> struct Hash {
	T MOD, p; 
	int n, neut = 'a'; //change to neuter value
	vector <T> h, pw;
	Hash (string &s, T MOD, T p) : MOD(MOD), p(p) { //change string for vector in case of needed
		n = s.size();
		h.resize(n);
		pw.resize(n);
		T b = 1;
		for (int i = 0; i < n; ++i) {
			h[i] = mul(s[i] - neut, b);
			if (i) h[i] = add(h[i], h[i - 1]);
			pw[i] = b;
			b  = mul(b, p);
		}
	}
	T add(T a, T b) { return a + b >= MOD ? a + b - MOD : a + b; }
	T sub(T a, T b) { return a >= b ? a - b : a - b + MOD; }
	T mul(T a, T b) { return 1ll * a * b % MOD; }
	T query(int l, int r, int x) { 
		//use x for shifting when comparing, in case of no need use x = 0
		return mul(pw[x], sub(h[r], l ? h[l - 1] : 0)); 
	}
};
