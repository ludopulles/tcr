NUM rotatingCalipers(vector<pt> &hull) {
	int n = hull.size(), a = 0, b = 1;
	if (n <= 1) return 0.0;
	while (((hull[1] - hull[0]) ^ (hull[(b + 1) % n] - hull[b])) > 0) b++;
	NUM ret = 0.0;
	while (a < n) {
		ret = max(ret, lenSq(hull[a], hull[b]));
		if (((hull[(a + 1) % n] - hull[a % n]) ^ (hull[(b + 1) % n] - hull[b])) <= 0) a++;
		else if (++b == n) b = 0;
	}
	return ret;
}
