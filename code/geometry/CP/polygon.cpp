typedef vector<point> poly;

// returns the perimeter: sum of Euclidean distances
// of consecutive line segments (polygon edges)
ld perimeter(const poly &P) {
  ld result = 0.0;
  REP(i, sz(P)-1) // remember that P[0] = P[n-1]
    result += dist(P[i], P[i+1]);
  return result; }

// returns the area, which is half the determinant
ld area(const poly &P) {
  ld result = 0.0;
  REP(i, sz(P)-1)
    result += P[i].x*P[i+1].y - P[i+1].x*P[i].y;
  return result;
}

// returns true if we always make the same turn
// throughout the polygon
bool isConvex(const poly &P) {
  int n = sz(P);
  if (n <= 3) return false; // point=2; line=3
  bool isLeft = ccw(P[0], P[1], P[2]);
  rep(i, n-2) if (ccw(P[i], P[i+1],
        P[(i+2) == n ? 1 : i+2]) != isLeft)
    return false; // different sign -> concave
  return true; } // convex

// returns true if pt is in polygon P
bool inPolygon(point pt, const poly &P) {
  if (sz(P) == 0) return false;
  ld sum = 0; // Assume P[0] == P[n-1]
  REP(i, sz(P)-1) {
    if (ccw(pt, P[i], P[i+1]))
         sum += angle(P[i], pt, P[i+1]);
    else sum -= angle(P[i], pt, P[i+1]); }
  return fabs(fabs(sum) - 2*PI) < EPS;
}

// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q,
      point A, point B) {
  ld a = B.y - A.y;
  ld b = A.x - B.x;
  ld c = B.x * A.y - A.x * B.y;
  ld u = fabs(a * p.x + b * p.y + c);
  ld v = fabs(a * q.x + b * q.y + c);
  return point((p.x*v + q.x*u) / (u+v),
               (p.y*v + q.y*u) / (u+v)); }

// cuts polygon Q along the line formed by a -> b
// (note: Q[0] == Q[n-1] is assumed)
poly cutPolygon(point a, point b, const poly &Q) {
  poly P;
  REP(i, sz(Q)) {
    ld left1 = cross(toVec(a,b), toVec(a,Q[i]));
    ld left2 = 0;
    if (i != sz(Q)-1)
      left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
    if (left1 > -EPS)
      P.pb(Q[i]); // Q[i] is left of ab
    if (left1 * left2 < -EPS)
      // edge Q[i]--Q[i+1] crosses line ab
      P.pb(lineIntersectSeg(Q[i], Q[i+1], a, b));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.pb(P.front()); // make P[0] == P[n-1]
  return P; }

point pivot; // sorts points by angle around pivot
bool angleCmp(point a, point b) {
  if (collinear(pivot, a, b)) // special case
    return dist(pivot, a) < dist(pivot, b);
  ld d1x = a.x - pivot.x, d1y = a.y - pivot.y;
  ld d2x = b.x - pivot.x, d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

poly CH(poly P) { // no order of P assumed!
  int i, j, n = sz(P)
  if (n <= 3) {
    // safeguard from corner case
    if (!(P[0] == P[n-1])) P.pb(P[0]);
    return P; // special case, the CH is P itself
  }

 // P0 = point with lowest Y (if tie rightmost X)
  int P0 = 0;
  rep(i, 1, n) if (P[i].y < P[P0].y
        || (P[i].y == P[P0].y && P[i].x > P[P0].x))
    P0 = i;
  // swap P[P0] with P[0]:
  point temp = P[0]; P[0] = P[P0]; P[P0] = temp;

  // second, sort points by angle w.r.t. pivot P0
  pivot = P[0];
  sort(++P.begin(), P.end(), angleCmp); // keep P[0]

  // third, the ccw tests
  poly S = { P[n-1], P[0], P[1] }; // initial S
  i = 2; // then, we check the rest
  while (i < n) { // required: N must be >= 3
    j = sz(S) - 1;
    if (ccw(S[j-1], S[j], P[i]))
      S.pb(P[i++]); // left turn, accept
    else // pop top of S when right turn
      S.pop_back();
  }
  return S;
}
