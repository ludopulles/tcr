vvi adj, comps;
vi tidx, lnk, cnr, st;
vector<bool> vis;
int age, ncomps;

void tarjan(int v) {
	tidx[v] = lnk[v] = ++age; vis[v] = true; st.pb(v);
	for (int w : adj[v]) {
		if(!tidx[w]) tarjan(w),lnk[v]=min(lnk[v],lnk[w]);
		else if(vis[w]) lnk[v] = min(lnk[v], tidx[w]);
	}
	if (lnk[v] != tidx[v]) return;
	comps.pb(vi());
	int w;
	do {
		vis[w = st.back()] = false; cnr[w] = ncomps;
		comps.back().pb(w);
		st.pop_back();
	} while (w != v);
	ncomps++;
}

void findSCC(int n) {
	age = ncomps = 0;
	vis.assign(n, false);
	tidx.assign(n, 0);
	lnk.resize(n); cnr.resize(n); comps.clear();
	for (int i = 0; i < n; i++)
		if (tidx[i] == 0) tarjan(i);
}
