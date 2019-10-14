vi topo(vvi &adj) { // requires C++14
	int n=sz(adj); vector<bool> vis(n,0); vi ans;
	auto dfs = [&](int v, const auto& f)->void {
		vis[v] = true;
		for (int w : adj[v]) if (!vis[w]) f(w, f);
		ans.pb(v);
	};
	REP(i, n) if (!vis[i]) dfs(i, dfs);
	reverse(all(ans));
	return ans;
}

