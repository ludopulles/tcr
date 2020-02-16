struct TwoSat {
	int n; SCC *scc = nullptr; vvi adj;
	TwoSat(int _n) : n(_n), adj(_n*2, vi()) {}
	~TwoSat() { delete scc; }
	
	// l => r, i.e. r is true or ~l
	void imply(int l, int r) {
		adj[n+l].pb(n+r); adj[n+(~r)].pb(n+(~l)); }
	void OR(int a, int b) { imply(~a, b); }
	void CONST(int a) { OR(a, a); }
	void IFF(int a, int b) { imply(a,b); imply(b,a); }

	bool solve(vector<bool> &sol) {
		delete scc; scc = new SCC(adj);
		REP(i, n) if (scc->cnr[n+i] == scc->cnr[n+(~i)])
			return false;
		vector<bool> seen(n, false);
		sol.assign(n, false);
		for (vi &cc : scc->comps) for (int v : cc) {
			int i = v<n ? n + (~v) : v - n;
			if (!seen[i]) seen[i]=true, sol[i] = v>=n;
		}
		return true;
	}
};
