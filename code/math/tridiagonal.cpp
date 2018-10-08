#define MAXN 5000
ld A[MAXN], B[MAXN], C[MAXN], D[MAXN], X[MAXN];
void solve(int n) {
  C[0] /= B[0]; D[0] /= B[0];
  rep(i,1,n-1) C[i] /= B[i] - A[i]*C[i-1];
  rep(i,1,n) D[i] = (D[i] - A[i]*D[i-1]) / (B[i] - A[i]*C[i-1]);
  X[n-1] = D[n-1];
  for (int i = n-1; i--;)
    X[i] = D[i] - C[i] * X[i+1]; }
