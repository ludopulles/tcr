const int maxn = 300;

struct edge { ll x, y, f, c, w; };
ll V, par[maxn], D[maxn]; vector<edge> g;
inline void addEdge(int u, int v, ll c, ll w) {
	g.pb({u, v, 0, c, w});
	g.pb({v, u, 0, 0, -w});
}

void sp(int s, int t) {
	fill_n(D, V, LLONG_MAX); D[s] = 0;
	for (int ng = g.size(), _ = V; _--; ) {
		bool ok = false;
		for (int i = 0; i < ng; i++)
			if (D[g[i].x] != LLONG_MAX && g[i].f < g[i].c && D[g[i].x] + g[i].w < D[g[i].y]) {
				D[g[i].y] = D[g[i].x] + g[i].w;
				par[g[i].y] = i; ok = true;
			}
		if (!ok) break;
	}
}

void minCostMaxFlow(int s, int t, ll &c, ll &f) {
	for (c = f = 0; sp(s, t), D[t] < LLONG_MAX; ) {
		ll df = LLONG_MAX, dc = 0;
		for (int v = t, e; e = par[v], v != s; v = g[e].x) df = min(df, g[e].c - g[e].f);
		for (int v = t, e; e = par[v], v != s; v = g[e].x) g[e].f += df, g[e^1].f -= df, dc += g[e].w;
		f += df; c += dc * df;
	}
}
