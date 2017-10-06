struct edge { int x, y, w; };
vector<edge> edges;

ll kruskal(int n) { // n: #vertices
	uf_init(n);
	sort(all(edges), [] (edge a, edge b) -> bool { return a.w < b.w; });
	ll ret = 0;
	for (edge e : edges)
		if (uf_find(e.x) != uf_find(e.y))
			ret += e.w, uf_union(e.x, e.y);
	return ret;
}
