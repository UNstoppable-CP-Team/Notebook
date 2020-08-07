typedef double T;
struct pt {
	T x, y;
	pt operator + (pt p) { return {x + p.x, y + p.y};}
	pt operator - (pt p) { return {x - p.x, y - p.y};}
	pt operator * (T d) { return {x * d, y * d};}
	pt operator / (T d) { return {x / d, y / d};}
	bool operator == (pt p) { return x == p.x && y == p.y;}
	bool operator != (pt p) {return x != p.x || y != p.y;}
};
T dot(pt a, pt b){
	return a.x*b.x+a.y*b.y;
}
T cross(pt a, pt b){
	return a.x*b.y-a.y*b.x;
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
