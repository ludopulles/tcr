vvi A; // A[i][j] is voor [i,j)

void divco(ll ls, ll rs, ll lt, ll rt, vi &t, vi &s) {
	// berekent t|_{[lt,rt)}
	if(lt >= rt) return;
	ll ms = ls, mt = (lt + rt)/2;
	t[mt] = -INF;
	rep(i,ls,rs) {
		if (i >= mt) break;
		if (s[i] + A[i][mt] > t[mt]) {
			t[mt] = s[i] + A[i][mt];
			ms = i;
		}
	}
	divco(ls,ms+1,lt,mt,t,s);
	divco(ms,rs,mt+1,rt,t,s);
}
