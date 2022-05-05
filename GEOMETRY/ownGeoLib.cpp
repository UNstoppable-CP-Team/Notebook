const long double pi = acos(-1);
typedef long double T;
struct pt {
	T x, y;
	pt(){}
	pt(T x, T y): x(x), y(y) {}
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
T cross(pt a, pt b){
	return a.x*b.y-a.y*b.x;
} T orient(pt a, pt b, pt c){// vectors A->B and A->C
	return cross(b-a, c-a);
}
T distancePoints(pt a, pt b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
const pt origen(0,0);
vector<pt> chull(vector<pt>& a, bool all_line = false){
	if(a.size() <= 3)return a;
	vector<pt> ans;
	for(auto& it : {0,1}){
		int start = ans.size();
		for(int i=0; i<a.size(); i++){
			while(ans.size() >= start + 2 && orient(ans[ans.size() - 2],ans[ans.size()-1],a[i])<=0){
				ans.pop_back();
			}
			ans.push_back(a[i]);
		}
		ans.pop_back();
		reverse(a.begin(),a.end());
	}
	return ans;
}
