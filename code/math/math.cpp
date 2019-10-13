int abs(int x) { return x > 0 ? x : -x; }
int sign(int x) { return (x > 0) - (x < 0); }

// greatest common divisor
ll gcd(ll a,ll b){while(b)a%=b,swap(a,b);return a;};
// least common multiple
ll lcm(ll a, ll b) { return a/gcd(a, b)*b; }
ll mod(ll a, ll b) { return (a%=b) < 0 ? a+b : a; }

// ab % m for m <= 4e18 in O(log b)
ll mod_mul(ll a, ll b, ll m) {
	ll r = 0;
	while(b) {
		if (b & 1) r = mod(r+a,m);
		a = mod(a+a,m); b >>= 1;
	}
	return r;
}

// a^b % m for m <= 2e9 in O(log b)
ll mod_pow(ll a, ll b, ll m) {
	ll r = 1;
	while(b) {
		if (b & 1) r = (r * a) % m; // mod_mul
		a = (a * a) % m; // mod_mul
		b >>= 1;
	}
	return r;
}

// returns x, y such that ax + by = gcd(a, b)
ll egcd(ll a, ll b, ll &x, ll &y) {
	ll xx = y = 0, yy = x = 1;
	while (b) {
		x -= a / b * xx; swap(x, xx);
		y -= a / b * yy; swap(y, yy);
		a %= b; swap(a, b);
	}
	return a;
}

// Chinese Remainder Theorem: returns (u, v) s.t.
// x=u (mod v) <=> x=a (mod n) and x=b (mod m)
pair<ll, ll> crt(ll a, ll n, ll b, ll m) {
	ll s, t, d = egcd(n, m, s, t); //n,m<=1e9
	if (mod(a - b, d)) return { 0, -1 };
	return { mod(s*b%m*n + t*a%n*m, n*m)/d, n*m/d };
}

// phi[i] = #{ 0 < j <= i | gcd(i, j) = 1 } sieve
vi totient(int N) {
	vi phi(N);
	for (int i = 0; i < N; i++) phi[i] = i;
	for (int i = 2; i < N; i++) if (phi[i] == i)
		for (int j = i; j < N; j+=i) phi[j] -= phi[j]/i;
	return phi;
}

// calculate nCk % p (p prime!)
ll lucas(ll n, ll k, ll p) {
	ll ans = 1;
	while (n) {
		ll np = n % p, kp = k % p;
		if (np < kp) return 0;
		ans = mod(ans * binom(np, kp), p); // (np C kp)
		n /= p; k /= p;
	}
	return ans;
}

// returns if n is prime for n < 3e24 (>2^64)
// but use mul_mod for n > 2e9.
bool millerRabin(ll n){
	if (n < 2 || n % 2 == 0) return n == 2;
	ll d = n - 1, ad, s = 0, r;
	for (; d % 2 == 0; d /= 2) s++;
	for (int a : {  2,  3,  5,  7, 11, 13,
				   17, 19, 23, 29, 31, 37, 41 }) {
		if (n == a) return true;
		if ((ad = mod_pow(a, d, n)) == 1) continue;
		for (r = 0; r < s && ad + 1 != n; r++)
			ad = (ad * ad) % n;
		if (r == s) return false;
	}
	return true;
}
