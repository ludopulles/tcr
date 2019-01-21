// minimum spanning forest actually...
vector<pii> edges[MAXN]; // or set
int dist[MAXN];
bool done[MAXN];

ll prim(int n) {
	fill_n(dist, n, INT_MAX); fill_n(done, n, false);
	ll ret = 0, trees = 0; set<pii> q; // (to MST, vertex)
	for (int i = 0; i < n; i++) {
		if (done[i]) continue;
		trees++;
		q.insert(pii(dist[i] = 0, i));
		while (!q.empty()) {
			ret += q.begin()->first;
			int cur = q.begin()->second;
			q.erase(q.begin());
			done[cur] = true;
			for (pii pr : edges[cur]) {
				if (!done[pr.x] && pr.y < dist[pr.x]) {
					q.erase(pii(dist[pr.x], pr.x));
					dist[pr.x] = pr.y;
					q.insert(pii(dist[pr.x], pr.x));
				}
			}
		}
	}
	// if (trees > 1) return -1; // forest
	return ret;
}
