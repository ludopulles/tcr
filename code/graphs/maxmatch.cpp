const int sizeL = 1e4, sizeR = 1e4;

bool vis[sizeR];
int par[sizeR]; // par : R -> L
vi adj[sizeL]; // adj : L -> (N -> R)

bool match(int u) {
	for (int v : adj[u]) {
		if (vis[v]) continue;
		vis[v] = true;
		if (par[v] == -1 || match(par[v])) {
			par[v] = u;
			return true;
		}
	}
	return false;
}

// perfect matching iff ret == sizeL == sizeR
int maxmatch() {
	fill_n(par, sizeR, -1);
	int ret = 0;
	for (int i = 0; i < sizeL; i++) {
		fill_n(vis, sizeR, false);
		ret += match(i);
	}
	return ret;
}
