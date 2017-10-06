struct edge { int x, y, w; };
edge edges[MAXM];

ll kruskal(int n, int m) { // n: #vertices, m: #edges
	uf_init(n);
	sort(edges, edges + m, [] (edge a, edge b) -> bool { return a.w < b.w; });
	ll ret = 0;
	while (m--) {
		if (uf_find(edges[m].x) == uf_find(edges[m].y)) continue;
		ret += edges[m].w; uf_union(edges[m].x, edges[m].y);
	}
	return ret;
}
