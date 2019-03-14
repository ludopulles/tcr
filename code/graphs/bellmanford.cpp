#define INFTY (1LL<<61LL)
// G undirected, (v,w) in G[u] 'n edge van u naar v lengte w
vi bellman_ford( vector<vii> G, ll s ) {
	ll n = G.size();
	vi d(n,INFTY); d[s] = 0; 
	rep( loops, 0, n )
		rep( u, 0, n ) if( d[u] != INFTY ) 
			for( ii e : G[u] )
				if( d[u] + e.y < d[e.x] )
					d[e.x] = d[u] + e.y;
	// detect paths of -INFTY length
	for( ll change = 1; change--; )
		rep( u, 0, n ) if( d[u] != INFTY )
			for( ii e : G[u] ) if( d[e.x] != -INFTY )
				if( d[u] + e.y < d[e.x] )
					d[e.x] = -INFTY, change = 1;
	return d;
}
