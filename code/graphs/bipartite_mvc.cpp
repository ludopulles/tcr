#include "hopcroft_karp.cpp"
vi alt;
void dfs( bi_graph &G, ll v ) {
	alt[v] = 1;
	for( ll u : G.adj[v] ) {
		alt[u+G.n] = 1;
		if( G.R[u] != G.n && !alt[G.R[u]] ) 
			dfs(G,G.R[u]); 
} }
vi mvc_bipartite( bi_graph &G ) {
	vi res; G.maximum_matching();
	alt.assign( G.n + G.m, 0 );
	rep(i,0,G.n) if( G.L[i] == -1 ) dfs(G,i);
	rep(i,0,G.n) if( !alt[i] ) res.pb(i);
	rep(i,0,G.n) if( alt[G.n+i] ) res.pb(G.n+i);
	return res; 
}
