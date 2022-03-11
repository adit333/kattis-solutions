/*https://ualberta.kattis.com/sessions/c2gb3k/problems/colouringbook

Approach:
- To check if all the points are connected, we have to find if all the points
    are in a single connected component. For this, we can run Kruskal's algorithm
    and check if the no. of mergers are greater than or equal to at least n-1;
    if so, there is a MST and hence all points are connected.
- Check if two lines don't intersect
- Check if dot lies on a line segment

To find the no. of rooms or bounding boxes, use Euler's Formula:
num_of_vertices - num_of_edges + num_of_rooms = num_of_components + 1
So, num_of_rooms = num_of_edges - num_num_of_verticesof_edges + 1 + 1
*/


#include <bits/stdc++.h>
using namespace std;

typedef tuple<int, int, int> iii;
typedef vector<int> vi;

constexpr int Colinear = -1, NoIntersect = 0, Intersect = 1;
constexpr int CW = 2, CCW = 3;
const double EPSILON = 0.000001;

// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                // OOP style
private:
  vi p, rank, setSize;                           // vi p is the key part
  int numSets;
public:
  UnionFind(int N) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    numSets = N;                                 // optional feature
  }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    setSize[y] += setSize[x];                    // combine set sizes at y
    --numSets;                                   // a union reduces numSets
  }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};


struct point {
    long double x, y;

    point(long double x_=0, long double y_=0) : x(x_), y(y_){}

    point operator - (const point& other) const {
        return point(this->x - other.x, this->y - other.y);
    }
    bool operator <(const point& other) const {
        return (x < other.x ? true : (x == other.x && y < other.y));
    }

    bool operator == (const point& other) const {
        return abs(other.x - x) < EPSILON && abs(other.y - y) < EPSILON;
    }
};

//Container for line segment
struct segment { point p1, p2; };


//Cross product, AB X AC
double cross(const point& A, const point& B, const point& C) {
    point AB = B - A, AC = C - A;
    return(AB.x * AC.y - AB.y * AC.x);
}

//Finds orientation of triplet of points p, q, r
//Returns Colinear, CW, or CCW
int orientation(const point& p, const point& q, const point& r)
{
    double val = cross(p, q, r);
    if(abs(val) < EPSILON) return Colinear;
    return (val > 0) ? CW : CCW;
}

//Checks if point p is possibly on the segment s
bool onSegment(const point& p, const segment& s)
{
    bool x = (abs(s.p1.x - s.p2.x) < EPSILON && abs(p.x - s.p2.x) < EPSILON) ||
              (p.x <= max(s.p1.x, s.p2.x) && p.x >= min(s.p1.x, s.p2.x));
    bool y = (abs(s.p1.y - s.p2.y) < EPSILON && abs(p.y - s.p2.y) < EPSILON) ||
              (p.y <= max(s.p1.y, s.p2.y) && p.y >= min(s.p1.y, s.p2.y));
    return x && y;
}

vector<point> intersect(const segment& s1, const segment& s2) {
    point a = s1.p1, b = s1.p2, c = s2.p1, d = s2.p2;

    if(orientation(a, b, c) == Colinear && orientation(a, b, d) == Colinear &&
        orientation(c, d, a) == Colinear && orientation(c, d, b) == Colinear)
    {
        point min_s1 = min(a, b), max_s1 = max(a, b);
        point min_s2 = min(c, d), max_s2 = max(c, d);

        if(max_s1 < min_s2 || max_s2 < min_s1) return {};

        point start = max(min_s1, min_s2), end = min(max_s1, max_s2);
        if(start == end)
            return {start};
        else
            return {min(start, end), max(start, end)};
    }

    long double a1 = b.y - a.y, a2 = d.y - c.y;
    long double b1 = a.x - b.x, b2 = c.x - d.x;
    long double c1 = a1*a.x + b1*a.y, c2 = a2*c.x + b2*c.y;
    long double det = a1*b2 - a2*b1;
    if (abs(det) > EPSILON)
    {
        point inter((b2*c1 - b1*c2)/det, (a1*c2 - a2*c1)/det);

        if (onSegment(inter, s1) && onSegment(inter, s2))
            return {inter};
    }
    return {};
}


bool is_single_component(int num_of_points, vector<pair<int,int>> &edges) {
    int u, v;
    int num_taken = 0;
    UnionFind UF(num_of_points);        // all V are disjoint sets
    for (int i = 0; i < edges.size(); ++i) {
        auto [u, v] = edges[i];
        if (UF.isSameSet(u, v))
            continue;                       // already in the same CC
        UF.unionSet(u, v);                  // merge them
        ++num_taken;                        // 1 more edge is taken
        if (num_taken == num_of_points-1)   // optimization
            break;
    }
    return num_taken == num_of_points - 1;
}


bool lines_intesect(vector<point> &points, vector<pair<int,int>> &lines) {
    for(auto l1 : lines) {
        for(auto l2 : lines) {
            // Don't check for intersection if the lines are intersecting at endpoints
            if (l1 == l2) continue;
            if (l1.first == l2.first) continue;
            if (l1.first == l2.second) continue;
            if (l1.second == l2.first) continue;
            if (l1.second == l2.second) continue;

            segment s1 = {points[l1.first], points[l1.second]};;
            segment s2 = {points[l2.first], points[l2.second]};;
            if (intersect(s1,s2).size() > 0)
                return true;
        }
    }
    return false;
}


bool point_lies_on_midlle_of_line(vector<point> &points, vector<pair<int,int>> &lines) {
    for (int j = 0; j < points.size(); j++) {           // for each point
        for (auto line : lines) {                       // for each line
            if (j == line.first || j == line.second)    // if point is not an endpoint of the line
                continue;
            segment s1 = {points[line.first], points[line.second]};;
            segment s2 = {points[j], points[j]};
            if (intersect(s1,s2).size() > 0)            // does the point lie on the line?
                return true;
        }
    }
    return false;
}

int main() {
    int num_of_points, num_of_lines;
    cin >> num_of_points >> num_of_lines;

    vector<point> points(num_of_points);
    for(auto& i : points)
        cin >> i.x >> i.y;

    vector<pair<int,int>> lines(num_of_lines);
    for(auto& i : lines)
        cin >> i.first >> i.second;

    if (!is_single_component(num_of_points, lines)) {
        cout << -1 << endl;
        return 0;
    }

    if (lines_intesect(points, lines)) {
        cout << -1 << endl;
        return 0;
    }

    if (point_lies_on_midlle_of_line(points, lines)) {
        cout << -1 << endl;
        return 0;
    }

    cout << lines.size() - points.size() + 2 << endl;
}
