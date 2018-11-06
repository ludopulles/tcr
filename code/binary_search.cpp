bool test(int n);

int search(int lo, int hi) {
	assert(test(lo) && !test(hi)); // BE CERTAIN
	while (hi - lo > 1) {
		int m = (lo + hi) / 2;
		(test(m) ? lo : hi) = m;
	}
	// assert(test(lo) && !test(hi));
	return lo;
}
