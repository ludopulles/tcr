struct bi_graph {
	int n, m, s; vvi G; vi L, R, d;
	bi_graph(int _n, int _m) : n(_n), m(_m), s(0),
			G(n), L(n,-1), R(m,n), d(n+1) {}
	void add_edge(int a, int b) { G[a].pb(b); }
	bool bfs() {
		queue<int> q; d[n] = LLONG_MAX;
		REP(v, n)
			if (L[v] < 0) d[v] = 0, q.push(v);
			else d[v] = LLONG_MAX;
		while (!q.empty()) {
			int v = q.front(); q.pop();
			if (d[v] >= d[n]) continue;
			for (int u : G[v]) if (d[R[u]] == LLONG_MAX)
				d[R[u]] = d[v]+1, q.push(R[u]);
		}
		return d[n] != LLONG_MAX;
	}
	bool dfs(int v) {
		if (v == n) return true;
		for (int u : G[v])
			if (d[R[u]] == d[v]+1 && dfs(R[u])) {
				R[u] = v; L[v] = u; return true;
			}
		d[v] = LLONG_MAX; return false;
	}
	int max_match() {
		while (bfs()) REP(i,n) s += L[i]<0 && dfs(i);
		return s;
	}

	void dfs2(int v, vector<bool> &alt) {
		alt[v] = true;
		for (int u : G[v]) {
			alt[u+n] = true;
			if (R[u] != n && !alt[R[u]]) dfs2(R[u], alt);
		}
	}

	vi min_vertex_cover() {
		vector<bool> alt(n+m, false); vi res;
		max_match();
		REP(i, n) if (L[i] < 0) dfs2(i, alt);
		// !alt[i] (i<n) OR alt[i] (i >= n)
		REP(i, n+m) if (alt[i] != (i<n)) res.pb(i);
		return res;
	}
};
