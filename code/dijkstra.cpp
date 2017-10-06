int n;
ll dist[MAXN];
vector<pii> edges[MAXN]; // (to, cost)

void dijkstra(int s) {
	fill_n(dist, MAXN, LLINF);
	vector<bool> vis(n, false);
	min_queue< pair<ll, ll> > q; // (dist, vertex)
	q.push(pair<ll, ll>(dist[s] = 0, s));

	while (!q.empty()) {
		pair<ll, ll> v = q.top(); q.pop();

		if (vis[v.y]) continue;
		vis[v.y] = true;

		for (const pii &e : edges[v.y]) {
			ll alt = v.x + e.y;
			if (alt >= dist[e.x]) continue;
			q.emplace(dist[e.x] = alt, e.x);
		}
	}
}
