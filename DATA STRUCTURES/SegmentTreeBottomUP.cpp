struct Stree{
	int n;
	vector<int> tree;
	Stree (int n) : n(n) {
		tree.assign(2*n+100,1e9+10);
	}
	void update(int k, int x){
		k += n;
		tree[k] = x;
		for(k>>=1; k; k>>=1) tree[k] = min(tree[k<<1],tree[(k<<1)|1]);
	}
	int query(int l, int r){
		int ans = 1e9+10;
		l += n, r+=n;
		while(l<=r){
			if(l&1) ans = min(ans,tree[l++]);
			if(!(r&1)) ans = min(ans,tree[r--]);
			l>>=1,r>>=1;
		}
		return ans;
	}
};
