const ll INF = 1LL << 61;
// G[u] = { (v,w) | edge u->v, cost w }
vi bellman_ford(vector<vii> G, ll s) {
	ll n = G.size();
	vi d(n, INF); d[s] = 0;
	REP(loops, n) REP(u, n) if(d[u] != INF)
		for(ii e : G[u]) if(d[u] + e.y < d[e.x])
			d[e.x] = d[u] + e.y;
	// detect paths of -INF length
	for( ll change = 1; change--; )
		REP(u, n) if(d[u] != INF)
			for(ii e : G[u]) if(d[e.x] != -INF)
				if(d[u] + e.y < d[e.x])
					d[e.x] = -INF, change = 1;
	return d;
}
