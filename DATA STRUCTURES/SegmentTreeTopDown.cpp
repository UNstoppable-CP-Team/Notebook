//Implementation required for lazy propagation and other applications
//Comlexity of queries, update and get (in every form) O(lg n)
const int maxn, NEUTER = 0; //Max number of array elements and neutral value of function f
int seg[4 * maxn], marked[4 * maxn]; //Segmentre itself, and auxiliar array for propagation
int f(int a, int b) {
	return a + b;
}
/*Details: tl = 0, tr = n - 1;
	   l, r, is the range we want to querie
	   v = 1
*/
//Single value update and queries
void update(int v, int tl, int tr, int pos, int val) {
	if(tr == tl) seg[v] += val;
	int tm = (tl + tr) / 2;
	if(pos <= tm) update(2 * v, tl, tm, pos, val);
	else update(2 * v + 1, tm + 1, tr, pos, val);
	seg[v] = f(seg[2 * v], seg[2 * v + 1]);
}
int querie(int v, int tl, int tr, int l, int r, int pos) {
	if(l > r) return NEUTER;
	if(tl == l && tr == r) return seg[v];
	int tm = (tl + tr) / 2;
	return f( querie(2 * v, tl, tm, l, min(tm, r), pos), querie(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
}
//Range update and queries
void update(int v, int tl, int tr, int l, int r, int val) {
	if(l > r) return;
	if(tl == l && tr == r) {
		seg[v] = val;
		marked[v] = 1;
	}
	push(v);
	int tm = (tl + tr) / 2;
	update(2 * v, tl, tm, l, min(tm, r), val);
	update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
}
int querie(int v, int tl, int tr, int l, int r, int pos) { //Beware of this one, not checked yed
	if(l > r) return NEUTER;
	if(tl == l && tr == r) return seg[v];
	int tm = (tl + tr) / 2;
	return seg[v] + f( querie(2 * v, tl, tm, l, min(tm, r), pos), querie(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
}
int get(int v, int tl, int tr, int pos) { //Single value querie
	if(tl == tr) return seg[v];
	int tm = (tl + tr)  >> 1;
	if(pos <= tm) return seg[v] + get(v << 1, tl, tm, pos);
	return seg[v] + get(v << 1 | 1, tm + 1, tr, pos);
}
///Using lazy propagation to set a[l, ..., r] = val;
void push(int& v) {
	if(marked[v]) {
		seg[2 * v] = seg[2 * v + 1] = seg[v];
		marked[2 * v] = marked[2 * v + 1] = 1;
		marked[v] = 0;
	}
}
void update(int v, int tl, int tr, int l, int r, int val) {
	if(l > r) return;
	if(tl == l && tr == r) {
		seg[v] = val;
		marked[v] = 1;
	}
	push(v);
	int tm = (tl + tr) / 2;
	update(2 * v, tl, tm, l, min(tm, r), val);
	update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
}
int get(int v, int tl, int tr, int pos) {
	if(tl == tr) return seg[v];
	push(v);
	int tm = (tl + tr)  >> 1;
	if(pos <= tm) return get(v << 1, tl, tm, pos);
	return  get(v << 1 | 1, tm + 1, tr, pos);
}
