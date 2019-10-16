#include "../datastructures/union_find.cpp"
struct arborescence {
  int n; union_find uf;
  vector<vector<pair<ii,int> > > adj;
  arborescence(int _n) : n(_n), uf(n), adj(n) { }
  void add_edge(int a, int b, int c) {
    adj[b].eb(ii(a,b),c); }
  vii find_min(int r) {
    vi vis(n,-1), mn(n,INT_MAX); vii par(n);
    REP(i, n) {
      if (uf.find(i) != i) continue;
      int at = i;
      while (at != r && vis[at] == -1) {
        vis[at] = i;
        for (auto it : adj[at])
          if (it.y < mn[at] && uf.find(it.x.x) != at)
            mn[at] = it.y, par[at] = it.x;
        if (par[at] == ii(0,0)) return vii();
        at = uf.find(par[at].x);
      }
      if (at == r || vis[at] != i) continue;
      union_find tmp = uf;
      vi seq;
      do seq.pb(at), at = uf.find(par[at].x);
      while (at != seq.front());
      int c = uf.find(seq[0]);
      for (auto it : seq) uf.unite(it, c);
      for (auto &jt : adj[c]) jt.y -= mn[c];
      for (auto it : seq) {
        if (it == c) continue;
        for (auto jt : adj[it])
          adj[c].eb(jt.x, jt.y - mn[it]);
        adj[it].clear();
      }
      vii rest = find_min(r);
      if (rest.empty()) return rest;
      ii use = rest[c];
      rest[at = tmp.find(use.y)] = use;
      for (int it : seq) if (it != at)
        rest[it] = par[it];
      return rest;
    }
    return par; } };
