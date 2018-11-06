struct dsu {
	vi par, rnk;
	dsu(int n) : par(n, -1), rnk(n, 0) {}
	int find(int i) { return
		par[i] < 0 ? i : par[i] = find(par[i]); }
	void unite(int a, int b) {
		if ((a = find(a)) == (b = find(b))) return;
		if (rnk[a] < rnk[b]) swap(a, b);
		if (rnk[a] == rnk[b]) rnk[a]++;
		par[a] += par[b]; par[b] = a;
	}
};
