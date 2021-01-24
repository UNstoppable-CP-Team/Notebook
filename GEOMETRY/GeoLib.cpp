typedef double T;
struct pt {
	T x, y;
	pt operator + (pt p) { return {x + p.x, y + p.y};}
	pt operator - (pt p) { return {x - p.x, y - p.y};}
	pt operator * (T d) { return {x * d, y * d};}
	pt operator / (T d) { return {x / d, y / d};}
	bool operator == (pt p) { return x == p.x && y == p.y;}
	bool operator != (pt p) {return x != p.x || y != p.y;}
	bool operator < (const pt &o) const{
		return x<o.x || (x==o.x && y<o.y);
	}
};
T dot(pt a, pt b){
	return a.x*b.x+a.y*b.y;
}
T cross(pt a, pt b){
	return a.x*b.y-a.y*b.x;
}
T orient(pt a, pt b, pt c){// vectors A->B and A->C
	return cross(b-a, c-a);
}
double angle(pt a){
	complex<T> pnt(a.x,b.y);
	return arg(pnt);//randians
}
double area(vector<pt>& p){
	T ans = 0;
	int n = p.size();
	for(int i=0; i<n; i++)
		ans += cross(p[i],p[(i+1)%n]);
	return abs(ans)/2.0;
}
// Polar sort --------------------------------------------------------------------
int side(pt p){
	assert(p.x != 0 && p.y !=0);
	retunr !(p.y>0 || (p.y == 0 && p.x<0));
}
pt o = {0,0} // origin
bool comp(const pt &a, const pt &b){
	return make_tuple(side(a-o),0) < make_tuple(side(b-o), corss(b-o, a-o));
}
//--------------------------------------------------------------------------------
//Convex hull --------------------------------------------------------------------
vector<pt> convex_hull(vector<pt> p){
	// To do
}
//-----------------------------------------------------------------------------
