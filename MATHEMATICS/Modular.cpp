template <int MOD> struct Modular {
	int value;
	static const int MOD_value = MOD;
	Modular(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
	Modular(long long a, long long b) : value(0){ *this += a; *this /= b;}
	Modular& operator+=(Modular const& b) {value += b.value; if (value >= MOD) value -= MOD; return *this;}
	Modular& operator-=(Modular const& b) {value -= b.value; if (value < 0) value += MOD;return *this;}
	Modular& operator*=(Modular const& b) {value = (long long)value * b.value % MOD;return *this;}
	friend Modular powmod(Modular a, long long e) {
		Modular res = 1; while (e) { if (e&1) res *= a; a *= a; e >>= 1; }
		return res;
	}
	friend Modular inv(Modular a) { return powmod(a, MOD - 2); }
	Modular& operator/=(Modular const& b) { return *this *= inv(b); }
	friend Modular operator+(Modular a, Modular const b) { return a += b; }
	friend Modular operator-(Modular a, Modular const b) { return a -= b; }
	friend Modular operator-(Modular const a) { return 0 - a; }
	friend Modular operator*(Modular a, Modular const b) { return a *= b; }
	friend Modular operator/(Modular a, Modular const b) { return a /= b; }
	friend std::ostream& operator<<(std::ostream& os, Modular const& a) {return os << a.value;}
	friend bool operator==(Modular const& a, Modular const& b) {return a.value == b.value;}
	friend bool operator!=(Modular const& a, Modular const& b) {return a.value != b.value;}
}; 
usgin Mint = Modular<(int)1e9 + 7>;

vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

Mint C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    inv_fact.push_back(1 / fact.back());
  }
  return fact[n] * inv_fact[k] * inv_fact[n - k];
}
