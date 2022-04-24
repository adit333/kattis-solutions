/*https://ualberta.kattis.com/sessions/c2gb3k/problems/wrapping

Approach:
    - Read in all the cooridnates, compute all the 4 coordiantes of the rectangle,
        making sure to account for the rotation.
        Note that the angle of the given rotation is clockwise, so the rotation matrix
        will be [cos -sin;  sin cos]
    - Compute the convex hull
    - Calculate the area of the polygon formed by the covex hull.
    - Return the calculated percentage.
*/

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

double DEG_to_RAD(double d) { return d*M_PI / 180.0; }

double RAD_to_DEG(double r) { return r*180.0 / M_PI; }

struct point { 
    double x, y; 
    point() {}
    point(double x, double y) : x(x), y(y) {}
    point(const point &p) : x(p.x), y(p.y) {}
    point operator + (const point &p) const { return point(x+p.x, y+p.y); }
    point operator - (const point &p) const { return point(x-p.x, y-p.y); }
    point operator * (double c) const { return point(x*c, y*c); }
    point operator / (double c) const { return point(x/c, y/c); }
    bool operator < (const point &p) const { return x < p.x || (x == p.x && y < p.y); }
    bool operator == (point other) const {
    return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); }
};

struct vec { double x, y;  // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y); }               // return double

// returns the perimeter of polygon P, which is the sum of
// Euclidian distances of consecutive line segments (polygon edges)
double perimeter(const vector<point> &P) {       // by ref for efficiency
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // note: P[n-1] = P[0]
    ans += dist(P[i], P[i+1]);                   // as we duplicate P[0]
  return ans;
}

// returns the area of polygon P
double area(const vector<point> &P) {
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // Shoelace formula
    ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
  return fabs(ans)/2.0;                          // only do / 2.0 here
}

double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// returns the area of polygon P, which is half the cross products
// of vectors defined by edge endpoints
double area_alternative(const vector<point> &P) {
  double ans = 0.0; point O(0.0, 0.0);           // O = the Origin
  for (int i = 0; i < (int)P.size()-1; ++i)      // sum of signed areas
    ans += cross(toVec(O, P[i]), toVec(O, P[i+1]));
  return fabs(ans)/2.0;
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

vector<point> CH_Graham(vector<point> &Pts) {    // overall O(n log n)
  vector<point> P(Pts);                          // copy all points
  int n = (int)P.size();
  if (n <= 3) {                                  // point/line/triangle
    if (!(P[0] == P[n-1])) P.push_back(P[0]);    // corner case
    return P;                                    // the CH is P itself
  }

  // first, find P0 = point with lowest Y and if tie: rightmost X
  int P0 = min_element(P.begin(), P.end())-P.begin();
  swap(P[0], P[P0]);                             // swap P[P0] with P[0]

  // second, sort points by angle around P0, O(n log n) for this sort
  sort(++P.begin(), P.end(), [&](point a, point b) {
    return ccw(P[0], a, b);                      // use P[0] as the pivot
  });

  // third, the ccw tests, although complex, it is just O(n)
  vector<point> S({P[n-1], P[0], P[1]});         // initial S
  int i = 2;                                     // then, we check the rest
  while (i < n) {                                // n > 3, O(n)
    int j = (int)S.size()-1;
    if (ccw(S[j-1], S[j], P[i]))                 // CCW turn
      S.push_back(P[i++]);                       // accept this point
    else                                         // CW turn
      S.pop_back();                              // pop until a CCW turn
  }
  return S;                                      // return the result
}


int main() {
    int t; cin >> t;    
    while (t--){
        int n; cin >> n;
        vector<point> points(4*n);
        double x,y,w,h,v,area_of_boards=0;
        for (int i=0;i<4*n;i+=4){
            cin >> x >> y >> w >> h >> v;
            area_of_boards += w*h;
            v = DEG_to_RAD(v);
            point h2(sin(v),cos(v)), w2(-cos(v),sin(v)), p(x,y);
            h2 = h2*(h/2); w2 = w2*(w/2);
            points[i] = p + h2 + w2;
            points[i+1] = p + h2 - w2;
            points[i+2] = p - h2 + w2;
            points[i+3] = p - h2 - w2;
        }
        auto convex_hull = CH_Graham(points);
        double area_of_convex_hull = area(convex_hull);
        double ratio = area_of_boards / area_of_convex_hull * 100;
        printf("%.1lf %%\n", ratio);
    }
    return 0;
}