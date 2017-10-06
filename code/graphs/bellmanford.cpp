vector< pair<pii, ll> > edges; // ((from, to), weight)
vector<ll> dist;

// when undirected, add back edges
bool bellman_ford(int V, int source) {
	dist.assign(V, 1e18); dist[source] = 0;
	
	bool updated = true; int loops = 0;
	while (updated && loops < n) {
		updated = false;
		for (auto e : edges) {
			int alt = dist[e.x.x] + e.y;
			if (alt < dist[e.x.y]) {
				dist[e.x.y] = alt; updated = true;
			}
		}
	}
	return loops < n; // loops >= n: negative cycles
}
