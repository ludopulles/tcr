#define MAXN 100100
struct RMST {
  struct point {
    int i; ll x, y;
    point() : i(-1) { }
    ll d1() { return x + y; }
    ll d2() { return x - y; }
    ll dist(point other) {
      return abs(x - other.x) + abs(y - other.y); }
    bool operator <(const point &other) const {
      return y==other.y ? x > other.x : y < other.y;
    }
  } best[MAXN], A[MAXN], tmp[MAXN];
  int n;
  RMST() : n(0) {}
  void add_point(int x, int y) {
    A[A[n].i = n].x = x, A[n++].y = y; }
  void rec(int l, int r) {
    if (l >= r) return;
    int m = (l+r)/2;
    rec(l,m), rec(m+1,r);
    point bst;
    for(int i=l, j=m+1, k=l; i <= m || j <= r; k++){
      if(j>r || (i <= m && A[i].d1() < A[j].d1())){
        tmp[k] = A[i++];
        if (bst.i != -1 && (best[tmp[k].i].i == -1
            || best[tmp[k].i].d2() < bst.d2()))
          best[tmp[k].i] = bst;
      } else {
        tmp[k] = A[j++];
        if (bst.i == -1 || bst.d2() < tmp[k].d2())
          bst = tmp[k]; } }
    rep(i,l,r+1) A[i] = tmp[i]; }
  vector<pair<ll,ii> > candidates() {
    vector<pair<ll, ii> > es;
    REP(p, 2) {
      REP(q, 2) {
        sort(A, A+n);
        REP(i, n) best[i].i = -1;
        rec(0, n-1);
        REP(i, n) {
          if(best[A[i].i].i != -1)
            es.pb({A[i].dist(best[A[i].i]),
                  {A[i].i, best[A[i].i].i}});
          swap(A[i].x, A[i].y);
          A[i].x *= -1, A[i].y *= -1; } }
      REP(i, n) A[i].x *= -1; }
    return es; } };
