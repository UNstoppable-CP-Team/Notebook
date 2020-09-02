//To solve the ecuaton of the form a*x + b*y = gcd(a, b);
//Complexity logarithmic
int gcdExtended(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = gcdExtended(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}
