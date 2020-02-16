// https://cp-algorithms.com/geometry/delaunay.html
typedef long long ll;

bool ge(const ll& a, const ll& b) { return a >= b; }
bool le(const ll& a, const ll& b) { return a <= b; }
bool eq(const ll& a, const ll& b) { return a == b; }
bool gt(const ll& a, const ll& b) { return a > b; }
bool lt(const ll& a, const ll& b) { return a < b; }
int sgn(const ll& a) { return (a>0) - (a<0); }

struct pt {
	ll x, y;
	pt() { }
	pt(ll _x, ll _y) : x(_x), y(_y) { }
	pt operator-(const pt& p) const {
		return pt(x - p.x, y - p.y); }
	ll cross(const pt& p) const {
		return x*p.y - y*p.x; }
	ll cross(const pt& a, const pt& b) const {
		return (a - *this).cross(b - *this); }
	ll dot(const pt& p) const {
		return x*p.x + y*p.y; }
	ll dot(const pt& a, const pt& b) const {
		return (a - *this).dot(b - *this); }
	ll lenSq() const { return this->dot(*this); }
	bool operator==(const pt& p) const {
		return eq(x, p.x) && eq(y, p.y); }
};

const pt inf_pt = pt(1e18, 1e18);

struct Quad { // `QuadEdge` originally
	pt O; // origin
	Quad *rot = nullptr, *onext = nullptr;
	bool used = false;
	Quad* rev() const { return rot->rot; }
	Quad* lnext() const {
		return rot->rev()->onext->rot; }
	Quad* oprev() const {
		return rot->onext->rot; }
	pt dest() const { return rev()->O; }
};

Quad* make_edge(pt from, pt to) {
	Quad* e1 = new Quad, e2 = new Quad;
	Quad* e3 = new Quad, e4 = new Quad;
	e1->O = from; e2->O = to;
	e3->O = e4->O = inf_pt;
	e1->rot = e3; e2->rot = e4;
	e3->rot = e2; e4->rot = e1;
	e1->onext = e1; e2->onext = e2;
	e3->onext = e4; e4->onext = e3;
	return e1;
}

void splice(Quad* a, Quad* b) {
	swap(a->onext->rot->onext, b->onext->rot->onext);
	swap(a->onext, b->onext);
}

void delete_edge(Quad* e) {
	splice(e, e->oprev());
	splice(e->rev(), e->rev()->oprev());
	delete e->rot; delete e->rev()->rot;
	delete e; delete e->rev();
}

Quad* connect(Quad* a, Quad* b) {
	Quad* e = make_edge(a->dest(), b->O);
	splice(e, a->lnext());
	splice(e->rev(), b);
	return e;
}

bool left_of(pt p, Quad* e) {
	return gt(p.cross(e->O, e->dest()), 0); }
bool right_of(pt p, Quad* e) {
	return lt(p.cross(e->O, e->dest()), 0); }

template <class T> T det3(T a1, T a2, T a3,
		T b1, T b2, T b3, T c1, T c2, T c3) {
	return a1*(b2*c3 - c2*b3) - a2*(b1*c3 - c1*b3)
		+ a3*(b1*c2 - c1*b2);
}

// Calculate directly with __int128, or with angles
bool in_circle(pt a, pt b, pt c, pt d) {
#if defined(__LP64__) || defined(_WIN64)
	__int128 det = 0;
	det -= det3<__int128>(b.x,b.y,b.lenSq(),
		c.x,c.y,c.lenSq(), d.x,d.y,d.lenSq());
	det += det3<__int128>(a.x,a.y,a.lenSq(),
		c.x,c.y,c.lenSq(), d.x,d.y,d.lenSq());
	det -= det3<__int128>(a.x,a.y,a.lenSq(),
		b.x,b.y,b.lenSq(), d.x,d.y,d.lenSq());
	det += det3<__int128>(a.x,a.y,a.lenSq(),
		b.x,b.y,b.lenSq(), c.x,c.y,c.lenSq());
	return det > 0;
#else
	auto ang = [](pt l, pt mid, pt r) {
		ll x = mid.dot(l, r), y = mid.cross(l, r);
		return atan2((ld) x, (ld) y);
	};
	return (ang(a,b,c) + ang(c,d,a)
		- ang(b,c,d) - ang(d,a,b)) > 1e-8;
#endif
}

pair<Quad*, Quad*> build_tr(int l, int r,
		vector<pt>& p) {
	if (r - l + 1 == 2) {
		Quad* res = make_edge(p[l], p[r]);
		return make_pair(res, res->rev());
	}
	if (r - l + 1 == 3) {
		Quad *a = make_edge(p[l], p[l+1]);
		Quad *b = make_edge(p[l+1], p[r]);
		splice(a->rev(), b);
		int sg = sgn(p[l].cross(p[l + 1], p[r]));
		if (sg == 0) return make_pair(a, b->rev());
		Quad* c = connect(b, a);
		if (sg == 1) return make_pair(a, b->rev());
		return make_pair(c->rev(), c);
	}
	int mid = (l + r) / 2;
	Quad *ldo, *ldi, *rdo, *rdi;
	tie(ldo, ldi) = build_tr(l, mid, p);
	tie(rdi, rdo) = build_tr(mid + 1, r, p);
	while (true) {
		if (left_of(rdi->O, ldi)) {
			ldi = ldi->lnext(); continue; }
		if (right_of(ldi->O, rdi)) {
			rdi = rdi->rev()->onext; continue; }
		break;
	}
	Quad* B = connect(rdi->rev(), ldi);
	auto valid = [&B](Quad* e) {
		return right_of(e->dest(), B); };

	if (ldi->O == ldo->O) ldo = B->rev();
	if (rdi->O == rdo->O) rdo = B;
	while (true) {
		Quad* lc = B->rev()->onext; // left candidate
		if (valid(lc)) {
			while (in_circle(B->dest(), B->O,
					lc->dest(), lc->onext->dest())) {
				Quad* t = lc->onext;
				delete_edge(lc);
				lc = t;
			}
		}
		Quad* rc = B->oprev(); // right candidate
		if (valid(rc)) {
			while (in_circle(B->dest(), B->O,
					rc->dest(), rc->oprev()->dest())) {
				Quad* t = rc->oprev();
				delete_edge(rc);
				rc = t;
			}
		}
		if (!valid(lc) && !valid(rc)) break;
		if (!valid(lc) || (valid(rc) && in_circle(
				lc->dest(), lc->O, rc->O, rc->dest())))
			B = connect(rc, B->rev());
		else B = connect(B->rev(), lc->rev());
	}
	return make_pair(ldo, rdo);
}

vector<tuple<pt, pt, pt>> delaunay(vector<pt> p) {
	sort(all(p), [](const pt& a, const pt& b) {
		return lt(a.x, b.x) ||
				(eq(a.x, b.x) && lt(a.y, b.y));
	});
	auto res = build_tr(0, sz(p) - 1, p);
	Quad* e = res.first;
	vector<Quad*> edges = {e};
	while(lt(e->onext->dest().cross(e->dest(),e->O),0))
		e = e->onext;
	auto add = [&p, &e, &edges]() {
		Quad* cur = e;
		do {
			cur->used = true;
			p.pb(cur->O);
			edges.pb(cur->rev());
			cur = cur->lnext();
		} while (cur != e);
	};
	add(); p.clear();

	int kek = 0;
	while (kek < sz(edges))
		if (!(e = edges[kek++])->used) add();
	vector<tuple<pt, pt, pt>> ans;
	for (int i = 0; i < sz(p); i += 3)
		ans.pb(make_tuple(p[i], p[i + 1], p[i + 2]));
	return ans;
}

