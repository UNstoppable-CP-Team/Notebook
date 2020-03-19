//To solve the ecuaton of the form a*x + b*y = gcd(a, b);
//Complexity logarithmic
int x, y, d;
void egcd(int  a, int  b){
	if (b==0){x =1; y = 0; d = a; return ;}
	egcd(b, a%b);
	int x1 = y, y1 = x - (a/b)*y;
	x = x1, y = y1;
}
