struct hasher {
	int b = 311, m; vi h, p;
	hasher(string s, int _m) :
			m(_m), h(sz(s)+1), p(sz(s)+1) {
		p[0] = 1; h[0] = 0;
		REP(i,sz(s)) p[i+1] = (ll)p[i] * b % m;
		REP(i,sz(s)) h[i+1] = ((ll)h[i] * b + s[i]) % m;
	}
	int hash(int l, int r) {
		return (h[r+1] + m - (ll)h[l]*p[r-l+1] % m) % m;
	}
};
