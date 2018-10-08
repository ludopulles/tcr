ll primitive_root(ll m) {
	vector<ll> div;
	for (ll i = 1; i*i < m; i++) {
		if ((m-1) % i == 0) {
			if (i < m) div.pb(i);
			if (m/i < m) div.pb(m/i); } }
	rep(x,2,m) {
		bool ok = true;
		for (ll d : div) 
			if (mod_pow(x, d, m) == 1) {
				ok = false; break; }
		if (ok) return x; }
	return -1; }
