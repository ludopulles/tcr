struct SCC {
	int n, age=0, ncomps=0; vvi adj, comps;
	vi tidx, lnk, cnr, st; vector<bool> vis;
	SCC(vvi &_adj) : n(sz(_adj)), adj(_adj),
			tidx(n, 0), lnk(n), cnr(n), vis(n, false) {
		REP(i, n) if (!tidx[i]) dfs(i);
	}

	void dfs(int v) {
		tidx[v] = lnk[v] = ++age;
		vis[v] = true; st.pb(v);
		for (int w : adj[v]) {
			if (!tidx[w])
				dfs(w), lnk[v] = min(lnk[v], lnk[w]);
			else if (vis[w]) lnk[v] = min(lnk[v], tidx[w]);
		}
		if (lnk[v] != tidx[v]) return;
		comps.pb(vi());
		int w;
		do {
			vis[w = st.back()] = false; cnr[w] = ncomps;
			comps.back().pb(w);
			st.pop_back();
		} while (w != v);
		ncomps++;
	}
};
