int abs(int x) { return x > 0 ? x : -x; }
int sign(int x) { return (x > 0) - (x < 0); }

// greatest common divisor
ll gcd(ll a, ll b) { while (b) a %= b, swap(a, b); return a; };
// least common multiple
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
ll mod(ll a, ll b) { return (a %= b) < 0 ? a + b : a; }

// safe multiplication (ab % m) for m <= 4e18 in O(log b)
ll mulmod(ll a, ll b, ll m) {
	ll r = 0;
	while (b) {
		if (b & 1) r = (r + a) % m; a = (a + a) % m; b >>= 1;
	}
	return r;
}

// safe exponentation (a^b % m) for m <= 2e9 in O(log b)
ll powmod(ll a, ll b, ll m) {
	ll r = 1;
	while (b) {
		if (b & 1) r = (r * a) % m; // r = mulmod(r, a, m);
		a = (a * a) % m; // a = mulmod(a, a, m);
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

// Chinese remainder theorem
const pll NO_SOLUTION(0, -1);
// Returns (u, v) such that x = u % v <=> x = a % n and x = b % m
pll crt(ll a, ll n, ll b, ll m) {
	ll s, t, d = egcd(n, m, s, t), nm = n * m;
	if (mod(a - b, d)) return NO_SOLUTION;
	return pll(mod(s * b * n + t * a * m, nm) / d, nm / d);
	/* when n, m > 10^6, avoid overflow:
	return pll(mod(mulmod(mulmod(s, b, nm), n, nm)
	             + mulmod(mulmod(t, a, nm), m, nm), nm) / d, nm / d); */
}

// phi[i] = #{ 0 < j <= i | gcd(i, j) = 1 }
vi totient(int N) {
	vi phi(N);
	for (int i = 0; i < N; i++) phi[i] = i;
	for (int i = 2; i < N; i++)
		if (phi[i] == i)
			for (int j = i; j < N; j += i) phi[j] -= phi[j] / i;
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

// returns if n is prime for n < 3e24 ( > 2^64)
bool millerRabin(ll n){
	if (n < 2 || n % 2 == 0) return n == 2;
	ll d = n - 1, ad, s = 0, r;
	for (; d % 2 == 0; d /= 2) s++;
	for (int a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 }) {
		if (n == a) return true;
		if ((ad = powmod(a, d, n)) == 1) continue;
		for (r = 0; r < s && ad + 1 != n; r++)
			ad = mulmod(ad, ad, n);
		if (r == s) return false;
	}
	return true;
}
