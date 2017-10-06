const double EPS = 1e-7, PI = acos(-1.0);

typedef long long NUM; // EITHER double OR long long
typedef pair<NUM, NUM> pt;
#define x first
#define y second

pt operator+(pt p, pt q) { return pt(p.x + q.x, p.y + q.y); }
pt operator-(pt p, pt q) { return pt(p.x - q.x, p.y - q.y); }

pt& operator+=(pt &p, pt q) { return p = p + q; }
pt& operator-=(pt &p, pt q) { return p = p - q; }

pt operator*(pt p, NUM l) { return pt(p.x * l, p.y * l); }
pt operator/(pt p, NUM l) { return pt(p.x / l, p.y / l); }

NUM operator*(pt p, pt q) { return p.x * q.x + p.y * q.y; }
NUM operator^(pt p, pt q) { return p.x * q.y - p.y * q.x; }

istream& operator>>(istream &in, pt &p) { return in >> p.x >> p.y; }
ostream& operator<<(ostream &out, pt p) { return out << '(' << p.x << ", " << p.y << ')'; }

NUM lenSq(pt p) { return p * p; }
NUM lenSq(pt p, pt q) { return lenSq(p - q); }
double len(pt p) { return hypot(p.x, p.y); } // more overflow safe
double len(pt p, pt q) { return len(p - q); }

typedef pt frac;
typedef pair<double, double> vec;
vec getvec(pt p, pt dp, frac t) { return vec(p.x + 1. * dp.x * t.x / t.y, p.y + 1. * dp.y * t.x / t.y); }

// square distance from pt a to line bc
frac distPtLineSq(pt a, pt b, pt c) {
	a -= b, c -= b;
	return frac((a ^ c) * (a ^ c), c * c);
}

// square distance from pt a to linesegment bc
frac distPtSegmentSq(pt a, pt b, pt c) {
	a -= b; c -= b;
	NUM dot = a * c, len = c * c;
	if (dot <= 0) return frac(a * a, 1);
	if (dot >= len) return frac((a - c) * (a - c), 1);
	return frac(a * a * len - dot * dot, len);
}

// projects pt a onto linesegment bc
frac proj(pt a, pt b, pt c) { return frac((a - b) * (c - b), (c - b) * (c - b)); }
vec projv(pt a, pt b, pt c) { return getvec(b, c - b, proj(a, b, c)); }

bool collinear(pt a, pt b, pt c) { return ((a - b) ^ (a - c)) == 0; }

bool pointOnSegment(pt a, pt b, pt c) {
	NUM dot = (a - b) * (c - b), len = (c - b) * (c - b);
	return collinear(a, b, c) && 0 <= dot && dot <= len;
}

// true => 1 intersection, false => parallel, so 0 or \infty solutions
bool linesIntersect(pt a, pt b, pt c, pt d) { return ((a - b) ^ (c - d)) != 0; }
vec lineLineIntersection(pt a, pt b, pt c, pt d) {
	double det = (a - b) ^ (c - d); pt ret = (c - d) * (a ^ b) - (a - b) * (c ^ d);
	return vec(ret.x / det, ret.y / det);
}

// dp, dq are directions from p, q
// intersection at p + t_i dp, for 0 <= i < return value
int segmentIntersection(pt p, pt dp, pt q, pt dq, frac &t0, frac &t1){
	if (dp * dp == 0) swap(p, q), swap(dp, dq); // dq = 0
	if (dp * dp == 0) { t0 = t1 = frac(0, 1); return p == q; } // dp = dq = 0
	pt dpq = (q - p); NUM c = dp ^ dq, c0 = dpq ^ dp, c1 = dpq ^ dq;
	if (c == 0) { // parallel, dp > 0, dq >= 0
		if (c0 != 0) return 0; // not collinear
		NUM v0 = dpq * dp, v1 = v0 + dq * dp, dp2 = dp * dp;
		if (v1 < v0) swap(v0, v1);
		t0 = frac(v0 = max(v0, (NUM) 0), dp2);
		t1 = frac(v1 = min(v1, dp2), dp2);
		return (v0 <= v1) + (v0 < v1);
	} else if (c < 0) c = -c, c0 = -c0, c1 = -c1;
	t0 = t1 = frac(c1, c);
	return 0 <= min(c0, c1) && max(c0, c1) <= c;
}

// Returns TWICE the area of a polygon to keep it an integer
NUM polygonTwiceArea(const vector<pt> &pts) {
	NUM area = 0;
	for (int N = pts.size(), i = 0, j = N - 1; i < N; j = i++)
		area += pts[i] ^ pts[j];
	return abs(area); // area < 0 <=> pts ccw
}

bool pointInPolygon(pt p, const vector<pt> &pts) {
	double sum = 0;
	for (int N = pts.size(), i = 0, j = N - 1; i < N; j = i++) {
		if (pointOnSegment(p, pts[i], pts[j])) return true; // boundary
		double angle = acos((pts[i] - p) * (pts[j] - p) / len(pts[i], p) / len(pts[j], p));
		sum += ((pts[i] - p) ^ (pts[j] - p)) < 0 ? angle : -angle;}
	return abs(abs(sum) - 2 * PI) < EPS;
}
