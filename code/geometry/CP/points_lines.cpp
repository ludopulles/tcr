const ld EPS = 1e-9;

ld DEG_to_RAD(ld d) { return d*PI/180.0; }
ld RAD_to_DEG(ld r) { return r*180.0/PI; }

struct point { ld x, y;
  point() { x = y = 0.0; }
  point(ld _x, ld _y) : x(_x), y(_y) {}
  // useful for sorting
  bool operator < (point other) const {
    if (fabs(x - other.x) > EPS)
      return x < other.x;
    return y < other.y; }
  // use EPS (1e-9) when testing for equality
  bool operator == (point other) const {
   return fabs(x-other.x)<EPS && fabs(y-other.y)<EPS;
  }
};

ld dist(point p1, point p2) {
  // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x - p2.x, p1.y - p2.y);
}
// rotate p by rad RADIANS CCW w.r.t origin (0, 0)
point rotate(point p, ld rad) {
  return point(p.x*cos(rad) - p.y*sin(rad),
               p.x*sin(rad) + p.y*cos(rad));
}

// lines are (x,y) s.t. ax + by = c. AND b=0,1.
struct line { ld a, b, c; };

// gives line throuhg p1, p2
line pointsToLine(point p1, point p2) {
  if (fabs(p1.x - p2.x) < EPS) // vertical line
    return { 1.0, 0.0, -p1.x };
  else return {
    -(ld)(p1.y - p2.y) / (p1.x - p2.x),
    1.0,
    -(ld)(l.a * p1.x) - p1.y;
  };
}

bool areParallel(line l1, line l2) {
  return fabs(l1.a-l2.a)<EPS && fabs(l1.b-l2.b)<EPS;
}

bool areSame(line l1, line l2) {
  return areParallel(l1,l2) && fabs(l1.c-l2.c)<EPS;
}

// returns true (+ intersection) if l1,l2 intersect
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false; // 0 or inf
  // solve two equations:
  p.x = (l2.b * l1.c - l1.b * l2.c)
      / (l2.a * l1.b - l1.a * l2.b);
  // special case: test for vertical line:
  if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
  else                  p.y = -(l2.a * p.x + l2.c);
  return true;
}

// name: `vec' is different from STL vector
struct vec { ld x, y;
  vec(ld _x, ld _y) : x(_x), y(_y) {} };
// convert 2 points to vector a->b
vec toVec(point a, point b) {
  return vec(b.x - a.x, b.y - a.y); }
vec scale(vec v, ld s) { return vec(v.x*s, v.y*s); }
// translate p according to v
point translate(point p, vec v) {
  return point(p.x + v.x , p.y + v.y); }

// convert point and gradient/slope to line
void pointSlopeToLine(point p, ld m, line &l) {
  l.a = -m; // always -m
  l.b = 1; // always 1
  l.c = -((l.a * p.x) + (l.b * p.y)); }

void closestPoint(line l, point p, point &ans) {
  if (fabs(l.b) < EPS) { // case 1: vertical line
    ans.x = -(l.c); ans.y = p.y; return; }

  if (fabs(l.a) < EPS) { // case 2: horizontal line
    ans.x = p.x; ans.y = -(l.c); return; }
  // normal line:
  line perpendicular;
  pointSlopeToLine(p, 1 / l.a, perpendicular);
  // intersect line l with this perpendicular line
  // the intersection point is the closest point
  areIntersect(l, perpendicular, ans); }

// returns the reflection of point on a line
void reflectionPoint(line l, point p, point &ans) {
  point b;
  closestPoint(l, p, b); // similar to distToLine
  return point(2*b.x - p.x, 2*b.y - p.y);

ld dot(vec a, vec b) { return a.x*b.x + a.y*b.y; }
ld cross(vec a,vec b){ return a.x*b.y - a.y*b.x; }
ld norm_sq(vec v)    { return v.x*v.x + v.y*v.y; }

// returns the distance from p to the line defined
// by points a and b (a != b), closest point in c.
ld distToLine(point p, point a, point b, point &c) {
 // formula: c = a + u * ab
  vec ap = toVec(a, p), ab = toVec(a, b);
  ld u = dot(ap, ab) / norm_sq(ab);
  c = translate(a, scale(ab, u));
  return dist(p, c); }

// returns the distance from p to the line segment
// ab defined by points a and b (still OK if a == b)
// the closest point is stored in c byref.
ld distToLineSegment(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  ld u = dot(ap, ab) / norm_sq(ab);
  if (u < 0.0) { c = point(a.x, a.y);
    return dist(p, a); } // closer to a
  if (u > 1.0) { c = point(b.x, b.y);
    return dist(p, b); } // closer to b
  // otherwise closest is perp to line:
  return distToLine(p, a, b, c); }

// returns angle aob in rad
ld angle(point a, point o, point b) {
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob)
      / sqrt(norm_sq(oa) * norm_sq(ob)));
}

// note: to accept collinear points, change `> 0'
// returns true if r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0; }

// returns true if r is on the same line as line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p,q), toVec(p,r))) < EPS;
}
