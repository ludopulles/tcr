void init2sat(int n) { adj.assign(2 * n, vi()); }

// (var xl = vl) ==> (var xr = vr)
void imply(int xl, bool vl, int xr, bool vr) {
	adj[2 * xl + vl].pb(2 * xr + vr);
	adj[2 * xr +!vr].pb(2 * xl +!vl);
}

void satOr(int xl, bool vl, int xr, bool vr) {
	imply(xl, !vl, xr, vr);
}
void satConst(int x, bool v) { imply(x, !v, x, v); }
void satIff(int xl, bool vl, int xr, bool vr) {
	imply(xl, vl, xr, vr); imply(xr, vr, xl, vl);}

bool solve2sat(int n, vector<bool> &sol) {
	findSCC(2 * n);
	for (int i = 0; i < n; i++)
		if (cnr[2 * i] == cnr[2 * i + 1]) return false;
	vector<bool> seen(n, false); sol.assign(n, false);
	for (vi &comp : comps) {
		for (int v : comp) {
			if (seen[v / 2]) continue;
			seen[v / 2] = true;
			sol[v / 2] = v & 1;
		}
	}
	return true;
}
