#define INFTY (1LL<<61LL)
void floyd_warshall( vvi& d ) {
	ll n = d.size();
	rep(i,0,n) rep(j,0,n) rep(k,0,n) 
		if( d[j][i] < INFTY and d[i][k] < INFTY )
			d[j][k] = max(-INFTY,min(d[j][k],d[j][i]+d[i][k]));
}
vvi d(n,vi(n,INFTY)); rep(i,0,n) d[i][i] = 0;
