int par[MAXN], rnk[MAXN];

void uf_init(int n) {
	fill_n(par, n, -1); fill_n(rnk, n, 0);
}

int uf_find(int v) { return par[v] < 0 ? v : par[v] = uf_find(par[v]); }

void uf_union(int a, int b) {
	if ((a = uf_find(a)) == (b = uf_find(b))) return;
	if (rnk[a] < rnk[b]) swap(a, b);
	if (rnk[a] == rnk[b]) rnk[a]++;
	par[b] = a;
}
