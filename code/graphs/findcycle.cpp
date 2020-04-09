// returns cycle in a connected undirected graph,
vi find_cycle(const vvi &G, int v0) { // if exists
	vi p(sz(G), -1), h(sz(G), 0), s{v0}; h[v0] = 1;
	while (!s.empty()) {
		int v = s.back(); s.pop_back();
		for (int w : G[v])
			if (!h[w]) s.pb(w), p[w] = v, h[w] = h[v]+1;
			else if (w != p[v]) {
				deque<int> cyc{v};
				while (v != w)
					if (h[v] > h[w]) cyc.pb(v = p[v]);
					else cyc.push_front(w), w = p[v];
				return vi(all(cyc));
			}
	}
	return {};
}
