//Complexity: O(log(n))
// Indexed 1 to n
int tree[N]; //N size of the array
int query(int k){
	int sum = 0;
	while(k>=1){
		sum+=tree[k];
		k -= k&-k;
	}
	return sum;
}
void update(int k, int x){
	while(k<=n){
		tree[k]+=x;
		k += k&-k;
	}
}
int query_range(int l, int r){
	return query(r)-query(l-1);
}
