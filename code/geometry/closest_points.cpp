int n;
pt pts[maxn];

struct byY {
	bool operator()(int a, int b) const { return pts[a].y < pts[b].y; }
};

inline NUM dist(pii p) {
	return hypot(pts[p.x].x - pts[p.y].x, pts[p.x].y - pts[p.y].y);
}

pii minpt(pii p1, pii p2) {
	return (dist(p1) < dist(p2)) ? p1 : p2;
}

// closest pts (by index) inside pts[l ... r], with sorted y values in ys
pii closest(int l, int r, vi &ys) {
	if (r - l == 2) { // don't assume 1 here.
		ys = { l, l + 1 };
		return pii(l, l + 1);
	} else if (r - l == 3) { // brute-force
		ys = { l, l + 1, l + 2 };
		sort(ys.begin(), ys.end(), byY());
		return minpt(pii(l, l + 1), minpt(pii(l, l + 2), pii(l + 1, l + 2)));
	}
	int m = (l + r) / 2;
	vi yl, yr;
	pii delta = minpt(closest(l, m, yl), closest(m, r, yr));
	NUM ddelta = dist(delta), xm = .5 * (pts[m-1].x + pts[m].x);
	merge(yl.begin(), yl.end(), yr.begin(), yr.end(), back_inserter(ys), byY());
	deque<int> q;
	for (int i : ys) {
		if (abs(pts[i].x - xm) <= ddelta) {
			for (int j : q) delta = minpt(delta, pii(i, j));
			q.pb(i);
			if (q.size() > 8) q.pop_front(); // magic from Introduction to Algorithms.
		}
	}
	return delta;
}
