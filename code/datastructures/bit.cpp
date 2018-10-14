struct BIT {
	int n;
	vector<ll> A;

	BIT(int _n) : n(_n), A(n, 0) {}
	// A[i] += v
	void update(int i, ll v) {
		while (i < n) A[i] += v, i += i & -i;
	}
	// returns sum_{0<j<=i} A[j]
	ll query(int i) {
		ll v = 0; while (i > 0) v += A[i], i -= i & -i; return v;
	}
};
