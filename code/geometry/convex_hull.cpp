// points are given by: pts[ret[0]], pts[ret[1]], ... pts[ret[ret.size()-1]]
vi convexHull(const vector<pt> &pts) {
	if (pts.empty()) return vi();
	vi ret;
	// find one outer point:
	int fsti = 0, n = pts.size();
	pt fstpt = pts[0];
	for(int i = n; i--; ) {
		if (pts[i] < fstpt) fstpt = pts[fsti = i];
	}
	ret.pb(fsti);
	pt refr = pts[fsti];

	vi ord; // index into pts
	for (int i = n; i--; ) {
		if (pts[i] != refr) ord.pb(i);
	}
	sort(ord.begin(), ord.end(), [&pts, &refr] (int a, int b) -> bool {
		NUM cross = (pts[a] - refr) ^ (pts[b] - refr);
		return cross != 0 ? cross > 0 : lenSq(refr, pts[a]) < lenSq(refr, pts[b]);
	});
	for (int i : ord) {
		// NOTE: > INCLUDES points on the hull-line, >= EXCLUDES
		while (ret.size() > 1 &&
				((pts[ret[ret.size()-2]]-pts[ret.back()]) ^ (pts[i]-pts[ret.back()])) >= 0)
			ret.pop_back();
		ret.pb(i);
	}
	return ret;
}
