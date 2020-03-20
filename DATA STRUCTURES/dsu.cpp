//Disjoint set union
int N; //Max number of nodes
int f[N], l[N]; //F: father array, l: length(size) array
int find(int n){return f[n] = f[n] == n ? n : find(f[n]);} // Complexity O(lgn), O(1) amortized
void merge(int a, int b){ //complexity O(1)
	a =  find(a), b = find(b);
	if(a == b) return;
	if(len[a] < len[b]) swap(a, b);
	f[b] = a, len[a]+=len[b];
}
void init(){
	for(int i=0; i<N; ++i) f[i] = i, len[i] = 1; //setting default values
}
