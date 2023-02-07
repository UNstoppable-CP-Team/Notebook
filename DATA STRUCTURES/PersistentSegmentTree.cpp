struct NodeValue{
	int longest = 0, len = 0, pref = 0, suf = 0;
	friend NodeValue operator + (const NodeValue& l, const NodeValue& r) {
		NodeValue ans;
		ans.pref = l.pref == l.len ? l.len + r.pref : l.pref;
		ans.suf = r.suf == r.len ? r.len + l.suf : r.suf;
		ans.longest = max({l.longest, r.longest, l.suf + r.pref, ans.pref, ans.suf});
		ans.len = l.len + r.len;
		return ans;
	}
};
NodeValue neuter;
struct Node {
	NodeValue value;
	Node* left = nullptr, *right = nullptr;

	Node(NodeValue value): value(value) {};
	Node(Node *l, Node* r) {
		left = l, right = r;
		if (!l) value = neuter + r->value;
		else if (!r) value = l->value + neuter;
		else value = l->value + r->value;
	}
};

const int maxn = 1e5 + 10;
int n;
Node* roots[maxn];

Node* build(int l = 0, int r = n - 1) {
	if (l == r) return new Node({0, 1, 0, 0});
	int mid = (l + r) / 2;
	return new Node(build(l, mid), build(mid + 1, r));
}
Node* update(Node* u, int val, int pos, int l = 0, int r = n - 1) {
	if (l == r) return new Node({val, 1, val, val}); 
	int mid = (l + r) / 2;
	if (pos > mid) return new Node(u->left, update(u->right, val, pos, mid + 1, r));
	return new Node(update(u->left, val, pos, l, mid), u->right);
}
NodeValue query(Node* u, int lo, int hi, int l = 0, int r = n - 1) {
	if (lo > r || hi < l || !u) return {0, 0, 0, 0};
	if (lo <= l && r <= hi) return u->value;
	int mid = (l + r) / 2;
	return query(u->left, lo, hi, l, mid) + query(u->right, lo, hi, mid + 1, r);
}
void printNode(Node* u) {
	cout << u->value.longest << ' ' << u->value.pref << ' ' << u->value.suf << ' ' << u->value.len;
}
void print(Node* u, int l = 0, int r = n - 1) {
	if (l > r || !u) return;
	cout << l << ' ' << r << ' ';
	printNode(u);
	cout << endl;
	int mid = (l + r) / 2;
	print(u->left, l, mid);
	print(u->right, mid + 1, r);
}

