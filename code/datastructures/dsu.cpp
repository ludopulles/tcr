struct dsu { vi p; dsu(int n) : p(n, -1) {}
	int find(int i) {
		return p[i] < 0 ? i : p[i] = find(p[i]); }
	void unite(int a, int b) {
		if ((a = find(a)) == (b = find(b))) return;
		if (p[a] > p[b]) swap(a, b);
		p[a] += p[b]; p[b] = a;
	}
};
