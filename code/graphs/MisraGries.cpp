struct Edge { int to, col, rev; };

struct MisraGries {
	int N, K=0; vvi F;
	vector<vector<Edge>> G;

	MisraGries(int n) : N(n), G(n) {}
	// add an undirected edge, NO DUPLICATES ALLOWED
	void addEdge(int u, int v) {
		G[u].pb({v, -1, (int) G[v].size()});
		G[v].pb({u, -1, (int) G[u].size()-1});
	}

	void color(int v, int i) {
		vi fan = { i };
		vector<bool> used(G[v].size());
		used[i] = true;
		for (int j = 0; j < (int) G[v].size(); j++)
			if (!used[j] && G[v][j].col >= 0 && F[G[v][fan.back()].to][G[v][j].col] < 0)
				used[j] = true, fan.pb(j), j = -1;
		int c = 0; while (F[v][c] >= 0) c++;
		int d = 0; while (F[G[v][fan.back()].to][d] >= 0) d++;
		int w = v, a = d, k = 0, ccol;
		while (true) {
			swap(F[w][c], F[w][d]);
			if (F[w][c] >= 0) G[w][F[w][c]].col = c;
			if (F[w][d] >= 0) G[w][F[w][d]].col = d;
			if (F[w][a^=c^d] < 0) break;
			w = G[w][F[w][a]].to;
		}
		do {
			Edge &e = G[v][fan[k]];
			ccol = F[e.to][d] < 0 ? d : G[v][fan[k+1]].col;
			if (e.col >= 0) F[e.to][e.col] = -1;
			F[e.to][ccol] = e.rev;
			F[v][ccol] = fan[k];
			e.col = G[e.to][e.rev].col = ccol;
			k++;
		} while (ccol != d);
	}
	// finds a K-edge-coloring
	void color() {
		REP(v, N) K = max(K, (int) G[v].size() + 1);
		F = vvi(N, vi(K, -1));
		REP(v, N) for (int i = G[v].size(); i--; )
			if (G[v][i].col < 0) color(v, i);
	}
};

