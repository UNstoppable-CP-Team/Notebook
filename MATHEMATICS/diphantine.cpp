//Using gcdExtended
pair<int,int> diophantine(int a, int b, int c){
  int x,y;
  int gcd = gcdExtended(a, b, x, y);
  assert(c%g==0); // There's no solution
  x *= c/g;
  y *= c/g;
  if( a < 0 ) x=-x;
  if( b < 0 ) y=-y;
  return {x,y};
}
