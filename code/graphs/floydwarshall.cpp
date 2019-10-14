const ll INF = 1LL << 61;
void floyd_warshall( vvi& d ) {
	ll n = d.size();
	REP(i,n) REP(j,n) REP(k,n)
		if(d[j][i] < INF && d[i][k] < INF) // neg edges!
			d[j][k] = max(-INF,
				min(d[j][k], d[j][i] + d[i][k]));
}

vvi d(n,vi(n,INF));
REP(i,n) d[i][i] = 0;
