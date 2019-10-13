const ld EPS = 1e-7, PI = acos(-1.0);
typedef ld NUM; // EITHER ld OR ll
typedef pair<NUM, NUM> pt;

pt operator+(pt p,pt q){ return {p.x+q.x,p.y+q.y}; }
pt operator-(pt p,pt q){ return {p.x-q.x,p.y-q.y}; }
pt operator*(pt p, NUM n) { return {p.x*n, p.y*n}; }

pt& operator+=(pt &p, pt q) { return p = p+q; }
pt& operator-=(pt &p, pt q) { return p = p-q; }

NUM operator*(pt p, pt q){ return p.x*q.x+p.y*q.y; }
NUM operator^(pt p, pt q){ return p.x*q.y-p.y*q.x; }

// square distance from p to line ab
ld distPtLineSq(pt p, pt a, pt b) {
	p -= a; b -= a;
	return ld(p^b) * (p^b) / (b*b);
}
// square distance from p to linesegment ab
ld distPtSegmentSq(pt p, pt a, pt b) {
	p -= a; b -= a;
	NUM dot = p*b, len = b*b;
	if (dot <= 0) return p*p;
	if (dot >= len) return (p-b)*(p-b);
	return p*p - ld(dot)*dot/len;
}
// Test if p is on line segment ab
bool segmentHasPoint(pt p, pt a, pt b) {
	pt u = p-a, v = p-b;
	return abs(u^v) < EPS && u*v <= 0;
}

// projects p onto the line ab
pair<ld,ld> proj(pt p, pt a, pt b) {
	p -= a; b -= a;
	return a + b*(ld(b*p) / (b*b));
}

bool col(pt a, pt b, pt c) {
	return abs((a-b) ^ (a-c)) < EPS;
}

// true => 1 intersection, false => parallel or same
bool linesIntersect(pt a, pt b, pt c, pt d) {
	return abs((a-b) ^ (c-d)) > EPS;
}

pair<ld,ld> lineLineIntersection(pt a, pt b, pt c, pt d) {
	ld det = (a-b) ^ (c-d);
	assert(abs(det) > EPS);
	return ((c-d)*(a^b) - (a-b)*(c^d)) * (ld(1.0)/det);
}

// dp, dq are directions from p, q
// intersection at p + t_i dp, for 0 <= i < return value
int segmentIntersection(pt p, pt dp, pt q, pt dq,
		pt &A, pt &B) {
	if (abs(dp * dp)<EPS)
		swap(p,q), swap(dp,dq); // dq=0
	if (abs(dp * dp)<EPS) {
		A = p; // dp = dq = 0
		return p == q;
	}

	pt dpq = q-p;
	NUM c = dp^dq, c0 = dpq^dp, c1 = dpq^dq;
	if (abs(c) < EPS) { // parallel, dp > 0, dq >= 0
		if (abs(c0) > EPS) return 0; // not collinear
		NUM v0 = dpq*dp, v1 = v0 + dq*dp, dp2 = dp*dp;
		if (v1 < v0) swap(v0, v1);

		v0 = max(v0, NUM(0));
		v1 = min(v1, dp2);

		A = p + dp * (ld(v0) / dp2);
		B = p + dp * (ld(v1) / dp2);

		return (v0 <= v1) + (v0 < v1);
	}

	if (c < 0) {
		c = -c; c0 = -c0; c1 = -c1;
	}

	A = p + dp * (ld(c1)/c);
	return 0 <= min(c0,c1) && max(c0,c1) <= c;
}

// Returns TWICE the area of a polygon (for integers)
NUM polygonTwiceArea(const vector<pt> &p) {
	NUM area = 0;
	for (int n = sz(p), i=0, j=n-1; i<n; j = i++)
		area += p[i] ^ p[j];
	return abs(area); // area < 0 <=> p ccw
}

bool insidePolygon(const vector<pt> &pts, pt p, bool strict = true) {
	int n = 0;
	for (int N = sz(pts), i = 0, j = N - 1; i < N; j = i++) {
		// if p is on edge of polygon
		if (segmentHasPoint(p, pts[i], pts[j])) return !strict;
		// or: if(distPtSegmentSq(p, pts[i], pts[j]) <= EPS) return !strict;

		// increment n if segment intersects line from p
		n += (max(pts[i].y, pts[j].y) > p.y && min(pts[i].y, pts[j].y) <= p.y &&
			(((pts[j] - pts[i])^(p-pts[i])) > 0) == (pts[i].y <= p.y));
	}
	return n & 1; // inside if odd number of intersections
}
