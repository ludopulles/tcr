const int maxn = 300;
struct edge {
	int x, y; ll f, c, w;
	edge(int _x, int _y, ll _c, ll _w) : x(_x), y(_y), f(0), c(_c), w(_w) {}
};
int nnodes, par[maxn]; ll dist[maxn]; vector<edge> g;
inline void addEdge(int f, int t, ll c, ll w) {
	g.eb(f, t, c, w); g.eb(t, f, 0, -w);
}

bool sp(int s, int t) {
	fill_n(dist, nnodes, LLINF); dist[s] = 0;
	for (int ng = g.size(), ntimes = nnodes; ntimes--; ) {
		bool ok = false;
		for (int i = 0; i < ng; i++)
			if (dist[g[i].x] != LLINF && g[i].f < g[i].c && dist[g[i].x] + g[i].w < dist[g[i].y]) {
				dist[g[i].y] = dist[g[i].x] + g[i].w;
				par[g[i].y] = i; ok = true;
			}
		if (!ok) break;
	}
	return dist[t] < LLINF;
}

pair<ll, ll> minCostMaxFlow(int N, int s, int t) {
	nnodes = N; ll c = 0, f = 0;
	while (sp(s, t)) {
		ll df = LLINF, dc = 0;
		for (int cur = t, e; e = par[cur], cur != s; cur = g[e].x)
			df = min(df, g[e].c - g[e].f);
		for (int cur = t, e; e = par[cur], cur != s; cur = g[e].x)
			g[e].f += df, g[e^1].f -= df, dc += g[e].w;
		f += df; c += dc * df;
	}
	return make_pair(c, f);
}
