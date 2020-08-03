typedef double T;
struct pt {
	T x, y;
	pt operator + (pt p) { return {x + p.x, y + p.y};}
	pt operator - (pt p) { return {x - p.x, y - p.y};}
	pt operator * (T d) { return {x * d, y * d};}
	pt operator / (T d) { return {x / d, y / d};}
	bool operator == (pt p) { return x == p.x && y == p.y;}
	bool operator != (pt p) {return x != p.x || y != p.y;}
	T dot (pt p) { return x * p.x + y * p.y;}
	T cross (pt p) { return x * p.y - y * p.x;}

};
