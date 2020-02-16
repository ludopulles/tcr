bool cycle_detection(const vvi &adj) {
	int n = sz(adj); // undirected graph
	stack<int> s;
	vector<bool> vis(n, false); vi par(n, -1);
	s.push(0); vis[0] = true;
	while (!s.empty()) {
		int cur = s.top(); s.pop();
		for (int i : adj[cur]) {
			if (vis[i] && par[cur] != i) return true;
			s.push(i); par[i] = cur; vis[i] = true;
		}
	}
	return false;
}
