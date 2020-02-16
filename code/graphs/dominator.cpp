const int N = 1e6;
vi g[N], g_rev[N], bucket[N];
int pos[N], cnt, order[N], par[N], sdom[N];
int p[N], best[N], idom[N], link[N];

void dfs(int v) {
	pos[v] = cnt;
	order[cnt++] = v;
	for (int u : g[v])
		if (pos[u] < 0) par[u] = v, dfs(u);
}

int find_best(int x) {
	if (p[x] == x) return best[x];
	int u = find_best(p[x]);
	if (pos[sdom[u]] < pos[sdom[best[x]]])
		best[x] = u;
	p[x] = p[p[x]];
	return best[x];
}

void dominators(int n, int root) {
	fill_n(pos, n, -1);
	cnt = 0;
	dfs(root);
	REP(i, n) for (int u : g[i]) g_rev[u].pb(i);
	REP(i, n) p[i] = best[i] = sdom[i] = i;

	for (int it = cnt - 1; it >= 1; it--) {
		int w = order[it];
		for (int u : g_rev[w]) {
			int t = find_best(u);
			if (pos[sdom[t]] < pos[sdom[w]])
				sdom[w] = sdom[t];
		}
		bucket[sdom[w]].pb(w);
		idom[w] = sdom[w];
		for (int u : bucket[par[w]])
			link[u] = find_best(u);
		bucket[par[w]].clear();
		p[w] = par[w];
	}

	for (int it = 1; it < cnt; it++) {
		int w = order[it];
		idom[w] = idom[link[w]];
	}
}
