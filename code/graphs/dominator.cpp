const int N = 1234567;

vi g[N], g_rev[N], bucket[N];
int pos[N], cnt, order[N], parent[N], sdom[N], p[N], best[N], idom[N], link[N];

void dfs(int v) {
  pos[v] = cnt;
  order[cnt++] = v;
  for (int u : g[v]) {
    if (pos[u] == -1) {
      parent[u] = v;
      dfs(u);
    }
  }
}

int find_best(int x) {
  if (p[x] == x) return best[x];
  int u = find_best(p[x]);
  if (pos[sdom[u]] < pos[sdom[best[x]]])
    best[x] = u;
  p[x] = p[p[x]];
  return best[x];
}

void dominators(int n, int root) {
  fill_n(pos, n, -1);
  cnt = 0;
  dfs(root);
  for (int i = 0; i < n; i++)
    for (int u : g[i]) g_rev[u].push_back(i);
  for (int i = 0; i < n; i++)
    p[i] = best[i] = sdom[i] = i;
  for (int it = cnt - 1; it >= 1; it--) {
    int w = order[it];
    for (int u : g_rev[w]) {
      int t = find_best(u);
      if (pos[sdom[t]] < pos[sdom[w]])
        sdom[w] = sdom[t];
    }
    bucket[sdom[w]].push_back(w);
    idom[w] = sdom[w];
    for (int u : bucket[parent[w]])
      link[u] = find_best(u);
    bucket[parent[w]].clear();
    p[w] = parent[w];
  }
  for (int it = 1; it < cnt; it++) {
    int w = order[it];
    idom[w] = idom[link[w]];
  }
}
