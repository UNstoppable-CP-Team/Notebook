//WARNING: IN CASE OF SEVERAL SEGMENT TREES CREATE A VECTOR, AND THEN PUSH_BACK() AS MANY TIMES AS NEEDED
template <class T> struct Stree{
	struct Node {
		T sum; Node *left, *right;
		Node() { sum = 0; left = right = nullptr; }
		void update(int tl, int tr, int pos, T val) {
			if (tl == tr) sum += val;
			else {
				int tm = (tl + tr) >> 1;
				if (pos <= tm) {
					if (!left) left = new Node();
					left->update(tl, tm, pos, val);
				} else {
					if (!right) right = new Node();
					right->update(tm + 1, tr, pos, val);
				}
				sum = 0;
				if (left) sum += left->sum;
				if (right) sum += right->sum;
			}
		}
		T query(int tl, int tr, int l, int r) {
			if (l > r) return 0;
			if (tl == l && tr == r) return sum;
			int tm = (tl + tr) >> 1;
			T ans = 0;
			if (left) ans += left->query(tl, tm, l, min(r, tm));
			if (right) ans += right->query(tm + 1, tr, max(l, tm + 1), r);
			return ans;
		}
	};
	int n; Node *root;
	Stree(int n) : n(n) { root = new Node(); }
	void update(int pos, T val) { root->update(0, n - 1, pos, val); }
	T query(int l, int r) { return root->query(0, n - 1, l, r); }
};
