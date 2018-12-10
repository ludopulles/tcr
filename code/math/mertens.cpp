const int L = 9e6;
int mob[L], mer[L];
unordered_map<ll,ll> mem;
ll M(ll n) {
  if (n < L) return mer[n];
  if (mem.find(n) != mem.end()) return mem[n];
  ll r = 1, d;
  for (d = 2; d * d <= n; d++) r -= M(n/d);
  for (d = n / --d; --d;) r -= mer[d]*(n/d-n/(d+1));
  return mer[n] = r; }
void sieve() {
  for (int i = 1; i < L; i++) mer[i] = mob[i] = 1;
  rep(i, 2, L) { if (mer[i]) for (int j=i; j<L; j+=i)
      mer[j]=0, mob[j]=(j/i)%i ? -mob[j/i] : 0;
    mer[i] = mob[i] + mer[i-1]; } }
