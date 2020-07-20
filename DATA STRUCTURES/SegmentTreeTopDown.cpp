//Implementation required for lazy propagation and other applications
const int maxn; //Max number of array elements
int seg[4 * maxn], marked[4 * maxn]; //Segmentre itself, and auxiliar array for propagation

//Single value update and queries
int f(int& a, int& b) {
	return a + b;
}
void update(int v, int tl, int tr, int pos, int val) {
	if(tr == tl) seg[v] += val;
	int tm = (tl + tr) / 2;
	if(pos <= tm) update(2 * v, tl, tm, pos, val);
	else update(2 * v + 1, tm + 1, tr, pos, val);
	seg[v] = f(seg[2 * v], seg[2 * v + 1]);
}
