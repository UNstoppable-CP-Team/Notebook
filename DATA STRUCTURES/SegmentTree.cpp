int n; //size of the array
int seg[2*n + 100], arr[n];
void add(int x, int k){ //add can be any operation min, max ...
	k+=n;
	seg[k] = x;
	for(k/=2; k>=1; k/=2) seg[k] = seg[k] + seg[2*k];
}
int sum(int a, int b){ //Just calculates the result in the given range
	a+=n, b+=n;
	int ans = 0;
	while(a<=b){
		if(a%2) ans += seg[a++];
		if(b%2 == 0) ans +=seg[b--];
		a/=2, b/=2;
	}
	return ans;
}
void build(){
  for(int i=0; i<n; ++i) add(arr[i], i);
}
