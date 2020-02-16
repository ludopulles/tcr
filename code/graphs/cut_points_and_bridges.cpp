const int MAXN = 5000;
int low[MAXN], num[MAXN], curnum;

void dfs(vvi &adj, vi &cp, vii &bs, int u, int p) {
  low[u] = num[u] = curnum++;
  int cnt = 0; bool found = false;
  REP(i, sz(adj[u])) {
    int v = adj[u][i];
    if (num[v] == -1) {
      dfs(adj, cp, bs, v, u);
      low[u] = min(low[u], low[v]);
      cnt++;
      found = found || low[v] >= num[u];
      if (low[v] > num[u]) bs.eb(u, v);
    } else if (p != v) low[u] = min(low[u], num[v]);
  }
  if (found && (p != -1 || cnt > 1)) cp.pb(u);
}

pair<vi,vii> cut_points_and_bridges(vvi &adj) {
  int n = size(adj);
  vi cp; vii bs;
  memset(num, -1, n << 2);
  curnum = 0;
  REP(i,n) if (num[i] < 0) dfs(adj, cp, bs, i, -1);
  return make_pair(cp, bs);
}
