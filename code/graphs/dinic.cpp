struct edge { ll t, r, c, f; };
int S, T, h[MAXN]; vector<edge> g[MAXN];

void addEdge(int u, int v, ll c) {
	g[u].pb({v, (ll)g[v].size(), c, 0});
	g[v].pb({u, (ll)g[u].size()-1,0,0});
}
void dinicBfs() {
	fill_n(h, MAXN, 0); h[S] = 1;
	queue<int> q; q.push(S);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (edge e : g[v]) if (!h[e.t] && e.f < e.c)
				h[e.t] = h[v]+1, q.push(e.t);
	}
}

ll dinicDFS(int v, ll mf) {
	if (v == T) return mf;
	ll f = 0; bool sat = true;
	for (edge &e : g[v]) {
		if (h[e.t] != h[v] + 1 || e.f >= e.c) continue;
		ll df = dinicDFS(e.t, min(mf - f, e.c - e.f));
		f += df, e.f += df, g[e.t][e.r].f -= df;
		sat &= e.f == e.c; if (mf == f) break;
	}
	if (sat) h[v] = 0;
	return f;
}

ll dinicMaxFlow(ll f = 0) {
	while (dinicBfs(), h[T]) f += dinicDFS(S, LLINF);
	return f;
}
