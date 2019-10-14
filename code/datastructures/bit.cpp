struct BIT {
	int n; vi A;
	BIT(int _n) : n(_n), A(_n+1, 0) {}
	BIT(vi &v) : n(sz(v)), A(1) {
		for (auto x:v) A.pb(x);
		for (int i=1, j; j=i&-i, i<=n; i++)
			if (i+j <= n) A[i+j] += A[i];
	}
	void update(int i, ll v) { // a[i] += v
		while (i <= n) A[i] += v, i += i&-i;
	}
	ll query(int i) { // sum_{j<=i} a[j]
		ll v = 0;
		while (i) v += A[i], i -= i&-i;
		return v;
	}
};

struct rangeBIT {
	int n; BIT b1, b2;
	rangeBIT(int _n) : n(_n), b1(_n), b2(_n+1) {}
	rangeBIT(vi &v) : n(sz(v)), b1(v), b2(sz(v)+1) {}
	void pupdate(int i, ll v) { b1.update(i, v); }
	void rupdate(int i, int j, ll v) { // a[i,..,j]+=v
		b2.update(i, v);
		b2.update(j+1, -v);
		b1.update(j+1, v*j);
		b1.update(i, (1-i)*v);
	}
	ll query(int i){return b1.query(i)+b2.query(i)*i;}
};
