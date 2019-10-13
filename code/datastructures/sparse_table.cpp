struct sparse_table {
	vvi m;
	sparse_table(vi arr) {
		m.pb(arr);
		for (int k=0; (1<<(++k)) <= sz(arr); ) {
			int w = (1<<k), hw = w/2;
			m.pb(vi(sz(arr) - w + 1);
			for (int i = 0; i+w <= sz(arr); i++) {
				m[k][i] = min(m[k-1][i], m[k-1][i+hw]);
			}
	}
	int query(int l, int r) { // query min in [l,r]
		int k = 31 - __builtin_clz(r-l); // k = 0;
		// while (1<<(k+1) <= r-l+1) k++;
		return min(m[k][l], m[k][r-(1<<k)+1]);
	}
};
