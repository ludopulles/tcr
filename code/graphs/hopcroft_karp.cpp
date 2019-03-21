#define INFTY (1LL<<61LL)

struct bi_graph {
	ll n, m;
	vvi adj;
	vi L, R, d;
	queue<ll> q;
	bi_graph( ll _n, ll _m ) : n(_n), m(_m), 
		adj(n), L(n,-1), R(m,n), d(n+1) {}
	ll add_edge( ll a, ll b ) { adj[a].pb(b); }
	ll bfs() {
		rep(v,0,n) 
			if( L[v] == -1 ) d[v] = 0, q.push(v);
			else d[v] = INFTY;
		d[n] = INFTY;
		while( !q.empty() ) {
			ll v = q.front(); q.pop();
			if( d[v] < d[n] ) 
				for( ll u : adj[v] ) if( d[R[u]] == INFTY )
					d[R[u]] = d[v]+1, q.push(R[u]);
		}
		return d[n] != INFTY;
	}
	ll dfs( ll v ) {
		if( v == n ) return true;
		for( ll u : adj[v] )
			if( d[R[u]] == d[v] + 1 and dfs(R[u]) ) {
				R[u] = v; L[v] = u;
				return true;
		}
		d[v] = INFTY;
		return false;
	}
	ll maximum_matching() {
		ll s = 0;
		while( bfs() ) rep(i,0,n)
			s += L[i] == - 1 && dfs( i );
		return s;
	} 
};