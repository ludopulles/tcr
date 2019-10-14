struct Edge { int t; ll c, f; };
struct Dinic {
	vi H, P; vvi E;
	vector<Edge> G;
	Dinic(int n) : H(n), P(n), E(n) {}

	void addEdge(int u, int v, ll c) {
		E[u].pb(G.size()); G.pb({v, c, 0LL});
		E[v].pb(G.size()); G.pb({u, 0LL, 0LL});
	}
	ll dfs(int t, int v, ll f) {
		if (v == t || !f) return f;
		for ( ; P[v] < (int) E[v].size(); P[v]++) {
			int e = E[v][P[v]], w = G[e].t;
			if (H[w] != H[v] + 1) continue;
			ll df = dfs(t, w, min(f, G[e].c - G[e].f));
			if (df > 0) {
				G[e].f += df, G[e ^ 1].f -= df;
				return df;
			}
		} return 0;
	}
	ll maxflow(int s, int t, ll f = 0) {
		while (1) {
			fill(all(H), 0); H[s] = 1;
			queue<int> q; q.push(s);
			while (!q.empty()) {
				int v = q.front(); q.pop();
				for (int w : E[v])
					if (G[w].f < G[w].c && !H[G[w].t])
						H[G[w].t] = H[v] + 1, q.push(G[w].t);
			}
			if (!H[t]) return f;
			fill(all(P), 0);
			while (ll df = dfs(t, s, LLONG_MAX)) f += df;
		}
	}
};
