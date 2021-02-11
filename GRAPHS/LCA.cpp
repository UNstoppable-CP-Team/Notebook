const int LOG2 = 20;
const int N = 1e5+10;
int depth[N];
int dp[N][LOG2];
void dfs(int u, int p=-1, int d){
	int depth[u] = d;
	dp[u][0] = p;
	for(int i=1; i<LOG2; i++){
		dp[u][i] = dp[dp[u][i-1]][i-1];
	for(int v: g[u]){
		if( v == p )continue;
		dfs(v,u,d+1);
	}
}
int lca(int a, int b){
	if(depth[a] < depth[b]) swap(a,b);
	int d = depth[a]-depth[b];
	for(in ti=0; i<LOG2; i++)
		if((d>>i & 1))
			a=dp[a][i];
	if( a==b ) return a;
	for(int i=LOG2-1; i>=0; i--){
		if(dp[a][i] != dp[b][i])
			a=dp[a][i],b=dp[b][i];
	}
	return dp[a][0];
}
