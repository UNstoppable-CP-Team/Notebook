//Nearest point from a line to a point P
//Complexity: O(1)

long double  distance(long double x,long double y,long double x1,long double y1,long double x2,long double y2){
  long double A = x - x1;
  long double B = y - y1;
  long double C = x2 - x1;
  long double D = y2 - y1;
  long double dot = A * C + B * D;
  long double len_sq = C * C + D * D;
  long double param = -1;
  long double xx,yy;
  if (len_sq != 0.0)
      param = dot / len_sq;
  if (param < 0.0){
    xx = x1;
    yy = y1;
  }else if (param > 1.0){
    xx = x2;
    yy = y2;
  }else{
    xx = x1 + param * C;
    yy = y1 + param * D;
    }
  long double dx = x - xx;
  long double dy = y - yy;
  return dx * dx + dy * dy;
}