vi sort_cyclic_shifts(const string &s) {
	const int alphabet = 256, n = sz(s);

	vi p(n), c(n), cnt(max(alphabet, n), 0);
	REP(i, n) cnt[s[i]]++;
	partial_sum(all(cnt), cnt.begin());
	REP(i, n) p[--cnt[s[i]]] = i;
	c[p[0]] = 0;
	int cl = 1;
	rep(i,1,n) {
		if (s[p[i]] != s[p[i-1]]) cl++;
		c[p[i]] = cl - 1;
	}

	vi pn(n), cn(n);
	for (int h = 0, l = 1; l < n; l*=2, ++h) {
		REP(i, n) {
			pn[i] = p[i] - (1 << h);
			if (pn[i] < 0) pn[i] += n;
		}
		fill(cnt.begin(), cnt.begin() + cl, 0);
		REP(i, n) cnt[c[pn[i]]]++;
		rep(i,1,cl) cnt[i] += cnt[i-1];
		for (int i = n-1; i >= 0; i--)
			p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0;
		cl = 1;
		rep(i, 1, n) {
			if (c[p[i]] != c[p[i-1]] || c[(p[i]+l)%n]
					!= c[(p[i-1]+l)%n]) cl++;
			cn[p[i]] = cl - 1;
		}
		c.swap(cn);
	}
	return p;
}

vi suffix_array(string s) {
	s += '\0';
	vi v = sort_cyclic_shifts(s);
	v.erase(v.begin());
	return v;
}
