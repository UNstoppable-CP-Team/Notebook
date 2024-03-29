typedef double T;
struct pt {
	T x, y;
	pt(T x, T y): x(x), y(y) {}
	pt(){}
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
	complex<T> pnt(a.x,a.y);
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
//depends on the problem, we have to modify this implementation
int side(pt p){
	assert(p.x != 0 || p.y !=0);
	return !(p.y>0 || (p.y == 0 && p.x<0));
}
pt o = {0,0} // origin
bool comp(const pt &a, const pt &b){
	return make_tuple(side(a-o),0) < make_tuple(side(b-o), cross(a-o, b-o));
}
//--------------------------------------------------------------------------------
//Convex hull --------------------------------------------------------------------
struct pt {
    double x, y;
};

int orientation(pt a, pt b, pt c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(pt a, pt b, pt c) { return orientation(a, b, c) == 0; }

void convex_hull(vector<pt>& a, bool include_collinear = false) {
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }

    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

    a = st;
}
//-----------------------------------------------------------------------------
//-----------Minkowski---------------------------------------------------------
void reorder_poly(vector<pt>& poly){
	sort(poly.begin(),poly.end(),[&](pt a, pt b){
			return (a.y < b.y) || (a.y == b.y && a.x < b.x);
			});
	o = poly.front(); //origin to use in polar sort
	sort(poly.begin()+1,poly.end(),polar_comp);
}
vector<pt> minkowski(vector<pt> P, vector<pt> Q){
	//sort by y then by x
	//and then polar sort
	reorder_poly(P);
	reorder_poly(Q);
	P.push_back(P[0]);
	P.push_back(P[1]);
	Q.push_back(Q[0]);
	Q.push_back(Q[1]);
	vector<pt> ret;
	int i =0, j = 0;
	while(i < int(P.size())-2 || j < int(Q.size()) - 2){
		ret.push_back(P[i] + Q[j]);
		long long crs = cross(P[i+1] - P[i],Q[j+1] - Q[j]);
		if(crs >= 0 && i < P.size() - 2)i++;
		if(crs <= 0 && j < Q.size() - 2)j++;
	}
	return ret;
}
//--------------------------------------------------------------------------------
