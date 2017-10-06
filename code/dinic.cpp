struct edge {
	int to, rev;
	ll cap, flow;
	edge(int t, int r, ll c) : to(t), rev(r), cap(c), flow(0) {}
};

int s, t, level[MAXN]; // s = source, t = sink
vector<edge> g[MAXN];

void add_edge(int fr, int to, ll cap) {
	g[fr].pb(edge(to, g[to].size(), cap));
	g[to].pb(edge(fr, g[fr].size() - 1, 0));
}

bool dinic_bfs() {
	fill_n(level, MAXN, 0);
	level[s] = 1;

	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (edge e : g[cur]) {
			if (level[e.to] == 0 && e.flow < e.cap) {
				level[e.to] = level[cur] + 1;
				q.push(e.to);
			}
		}
	}
	return level[t] != 0;
}

ll dinic_dfs(int cur, ll maxf) {
	if (cur == t) return maxf;

	ll f = 0;
	bool isSat = true;
	for (edge &e : g[cur]) {
		if (level[e.to] != level[cur] + 1 || e.flow >= e.cap)
			continue;
		ll df = dinic_dfs(e.to, min(maxf - f, e.cap - e.flow));
		f += df;
		e.flow += df;
		g[e.to][e.rev].flow -= df;
		isSat &= e.flow == e.cap;
		if (maxf == f) break;
	}
	if (isSat) level[cur] = 0;
	return f;
}

ll dinic_maxflow() {
	ll f = 0;
	while (dinic_bfs()) f += dinic_dfs(s, LLINF);
	return f;
}
