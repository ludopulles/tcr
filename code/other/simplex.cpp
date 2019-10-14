typedef vector<ld> VD;
typedef vector<VD> VVD;
const ld EPS = 1e-9;
struct LPSolver {
 int m, n; vi B, N; VVD D;
 LPSolver(const VVD &A, const VD &b, const VD &c) :
     m(b.size()), n(c.size()),
     N(n + 1), B(m), D(m + 2, VD(n + 2)) {
  REP(i, m) REP(j, n) D[i][j] = A[i][j];
  REP(i, m) { B[i] = n + i; D[i][n] = -1;
    D[i][n + 1] = b[i]; }
  REP(j, n) N[j] = j, D[m][j] = -c[j];
  N[n] = -1; D[m + 1][n] = 1;
 }
 void Pivot(int r, int s) {
  double inv = 1.0 / D[r][s];
  REP(i, m+2) if (i != r) REP(j, n+2) if (j != s)
    D[i][j] -= D[r][j] * D[i][s] * inv;
  REP(j, n+2) if (j != s) D[r][j] *= inv;
  REP(i, m+2) if (i != r) D[i][s] *= -inv;
  D[r][s] = inv;
  swap(B[r], N[s]); }
 bool Simplex(int phase) {
  int x = phase == 1 ? m + 1 : m;
  while (true) {
   int s = -1;
   for (int j = 0; j <= n; j++) {
    if (phase == 2 && N[j] == -1) continue;
    if (s == -1 || D[x][j] < D[x][s] ||
        D[x][j] == D[x][s] && N[j] < N[s]) s = j; }
   if (D[x][s] > -EPS) return true;
   int r = -1;
   REP(i, m) {
    if (D[i][s] < EPS) continue;
    if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] /
        D[r][s] || (D[i][n + 1] / D[i][s]) == (D[r][n + 1] /
        D[r][s]) && B[i] < B[r]) r = i; }
   if (r == -1) return false;
   Pivot(r, s); } }
 ld Solve(VD &x) {
  int r = 0;
  rep(i, 1, m) if (D[i][n+1] < D[r][n+1]) r = i;
  if (D[r][n + 1] < -EPS) {
   Pivot(r, n);
   if (!Simplex(1) || D[m + 1][n + 1] < -EPS)
     return -numeric_limits<ld>::infinity();
   REP(i, m) if (B[i] == -1) {
    int s = -1;
    for (int j = 0; j <= n; j++)
     if (s == -1 || D[i][j] < D[i][s] ||
         D[i][j] == D[i][s] && N[j] < N[s])
       s = j;
    Pivot(i, s); }
  }
  if (!Simplex(2)) return numeric_limits<ld>::infinity();
  x = VD(n);
  for (int i = 0; i < m; i++) if (B[i] < n)
    x[B[i]] = D[i][n + 1];
  return D[m][n + 1]; } };
// 2-phase simplex solves linear system:
//     maximize     c^T x
//     subject to   Ax <= b, x >= 0
// INPUT: A -- an m x n matrix
//        b -- an m-dimensional vector
//        c -- an n-dimensional vector
//        x -- optimal solution (by reference)
// OUTPUT: c^T x (inf. if unbounded above, nan if infeasible)
// *** Example ***
// const int m = 4, n = 3;
// ld _A[m][n] = {{6,-1,0}, {-1,-5,0},
//    {1,5,1}, {-1,-5,-1}};
// ld _b[m] = {10,-4,5,-5}, _c[n]= {1,-1,0};
// VVD A(m);
// VD b(_b, _b + m), c(_c, _c + n), x;
// REP(i, m) A[i] = VD(_A[i], _A[i] + n);
// LPSolver solver(A, b, c);
// ld value = solver.Solve(x);
// cerr << "VALUE: " << value << endl; // 1.29032
// cerr << "SOLUTION:"; // 1.74194 0.451613 1
// REP(i, sz(x)) cerr << " " << x[i];
// cerr << endl;
