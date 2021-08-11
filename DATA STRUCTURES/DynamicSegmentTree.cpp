//WARNING: IN CASE OF SEVERAL SEGMENT TREES CREATE A VECTOR, AND THEN PUSH_BACK() AS MANY TIMES AS NEEDED
template<class T> struct Node {
	int tl, tr;
	T neut = -1e18, sum;
	Node *left, *right;
	Node(int tl, int tr) : tl(tl), tr(tr) { sum = neut; left = right = nullptr; }
	T merge(T a, T b) { return max(a, b); }
	void update(int tl, int tr, int pos, T val) {
		if (tl == tr) sum = merge(val, sum);
		else {
			int tm = (tl + tr) >> 1;
			if (pos <= tm) {
				if (!left) left = new Node(tl, tm);
				left->update(tl, tm, pos, val);
			} else {
				if (!right) right = new Node(tm + 1, tr);
				right->update(tm + 1, tr, pos, val);
			}
			sum = neut;
			if (left) sum = merge(sum, left->sum);
			if (right) sum = merge(right->sum, sum);
		}
	}
	T query(int tl, int tr, int l, int r) {
		if (l > r) return neut;
		if (tl == l && tr == r) return sum;
		int tm = (tl + tr) >> 1;
		T ans = neut;
		if (left) ans = merge(left->query(tl, tm, l, min(r, tm)), ans);
		if (right) ans = merge(right->query(tm + 1, tr, max(l, tm + 1), r), ans);
		return ans;
	}
	void update(int pos, T val) { update(tl, tr, pos, val); }
	T query(int l, int r) { return query(tl, tr, l, r); }
};
