vvi adj; // assumes bidirected graph, adjust accordingly

bool cycle_detection() {
	stack<int> s;
	vector<bool> vis(MAXN, false);
	vi par(MAXN, -1);
	s.push(0);
	vis[0] = true;
	while(!s.empty()) {
		int cur = s.top();
		s.pop();
		for(int i : adj[cur]) {
			if(vis[i] && par[cur] != i) return true;
			s.push(i);
			par[i] = cur;
			vis[i] = true;
		}
	}
	return false;
}
