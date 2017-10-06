struct edge {
	// to, rev, flow, capacity, weight
	int t, r;
	ll f, c, w;
	edge(int _t, int _r, ll _c, ll _w) : t(_t), r(_r), f(0), c(_c), w(_w) {}
};

int n, par[MAXN];
vector<edge> adj[MAXN];
ll dist[MAXN];

bool findPath(int s, int t) {
	fill_n(dist, n, LLINF);
	fill_n(par, n, -1);

	priority_queue< pii, vector<pii>, greater<pii> > q;
	q.push(pii(dist[s] = 0, s));

	while (!q.empty()) {
		int d = q.top().x, v = q.top().y;
		q.pop();
		if (d > dist[v]) continue;

		for (edge e : adj[v]) {
			if (e.f < e.c && d + e.w < dist[e.t]) {
				q.push(pii(dist[e.t] = d + e.w, e.t));
				par[e.t] = e.r;
			}
		}
	}
	return dist[t] < INF;
}

pair<ll, ll> minCostMaxFlow(int s, int t) {
	ll cost = 0, flow = 0;
	while (findPath(s, t)) {
		ll f = INF, c = 0;
		int cur = t;
		while (cur != s) {
			const edge &rev = adj[cur][par[cur]], &e = adj[rev.t][rev.r];
			f = min(f, e.c - e.f);
			cur = rev.t;
		}
		cur = t;
		while (cur != s) {
			edge &rev = adj[cur][par[cur]], &e = adj[rev.t][rev.r];
			c += e.w;
			e.f += f;
			rev.f -= f;
			cur = rev.t;
		}
		cost += f * c;
		flow += f;
	}
	return pair<ll, ll>(cost, flow);
}

inline void addEdge(int from, int to, ll cap, ll weight) {
	adj[from].pb(edge(to, adj[to].size(), cap, weight));
	adj[to].pb(edge(from, adj[from].size() - 1, 0, -weight));
}
