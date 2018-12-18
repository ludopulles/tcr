// the convex hull consists of: { pts[ret[0]], pts[ret[1]], ... pts[ret.back()] }
vi convexHull(const vector<pt> &pts) {
	if (pts.empty()) return vi();
	vi ret, ord;
	int n = pts.size(), st = min_element(all(pts)) - pts.begin();
	rep(i, 0, n)
		if (pts[i] != pts[st]) ord.pb(i);
	sort(all(ord), [&pts,&st] (int a, int b) {
		pt p = pts[a] - pts[st], q = pts[b] - pts[st];
		return (p ^ q) != 0 ? (p ^ q) > 0 : lenSq(p) < lenSq(q);
	});
	ord.pb(st); ret.pb(st);
	for (int i : ord) {
		// use '>' to include ALL points on the hull-line
		for (int s = ret.size() - 1; s > 0 && ((pts[ret[s-1]] - pts[ret[s]]) ^ (pts[i] - pts[ret[s]])) >= 0; s--)
			ret.pop_back();
		ret.pb(i);
	}
	ret.pop_back();
	return ret;
}
