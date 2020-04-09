// (dist, prev)
pair<vi,vi> dijkstra(const vector<vii> &G, int s) {
	vi d(sz(G), LLONG_MAX), p(sz(G), -1);
	set<ii> Q{ ii{ d[s] = 0, s } }; // (dist[v], v)
	while (!Q.empty()) {
		int v = Q.begin()->y;
		Q.erase(Q.begin());
		for(ii e : G[v]) if (d[v] + e.y < d[e.x]) {
			Q.erase(ii(d[e.x], e.x));
			Q.emplace(d[e.x] = d[v] + e.y, e.x);
			p[e.x] = v;
		}
	}
	return {d, p};
}

