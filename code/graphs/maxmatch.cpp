vector<bool> vis; vi par; vvi adj; // L->{R,...}

bool match(int u) {
	for (int v : adj[u]) {
		if (vis[v]) continue;
		vis[v] = true;
		if (par[v] == -1 || match(par[v]))
			{ par[v] = u; return true; }
	}
	return false;
}

// perfect matching iff ret == L == R
int maxmatch(int L, int R) {
	par.assign(R, -1);
	int ret = 0;
	REP(i, L) vis.assign(R, false), ret += match(i);
	return ret;
}
