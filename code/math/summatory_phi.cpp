const int L = 1e7;
ll sp[L];
unordered_map<ll,ll> mem;
ll sumphi(ll n) {
  if (n < L) return sp[n];
  if (mem.find(n) != mem.end()) return mem[n];
  ll r = 0, d;
  for (d = 2; d * d <= n; d++) r += sumphi(n/d);
  for (d = n / --d; --d;) r += sp[d]*(n/d-n/(d+1));
  return mem[n] = n*(n+1)/2 - r; }
void sieve() {
  iota(sp, sp + L, 0);
  rep(i, 2, L) if (sp[i] == i)
    for(int j=i; j<L; j+=i) sp[j] -= sp[j]/i;
  rep(i, 2, L) sp[i] += sp[i-1]; }
