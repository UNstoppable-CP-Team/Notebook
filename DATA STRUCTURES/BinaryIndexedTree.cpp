//Complexity: O(log(n))
// Indexed 1 to n
struct bit{
	int n;
	vector<int> tree;
	bit (int n) : n(n){
		tree.assign(n+10,0);
	}
	void update(int k, int x){
		while(k<=n){
			tree[k] += x;
			k+=k&-k;
		}
	}
	int query(int k){
		int sum = 0;
		while(k>=1){
			sum+=tree[k];
			k-=k&-k;
		}
		return sum;
	}
	int query_range(int l, int r){
		return query(r)-query(l-1);
	}
};

