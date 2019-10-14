struct edge { int x, y; ll w; };
ll kruskal(int n, vector<edge> edges) {
	dsu D(n);
	sort(all(edges), [] (edge a, edge b) -> bool {
		return a.w < b.w; });
	ll ret = 0;
	for (edge e : edges)
		if (D.find(e.x) != D.find(e.y))
			ret += e.w, D.unite(e.x, e.y);
	return ret;
}
