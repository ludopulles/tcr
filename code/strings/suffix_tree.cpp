const int N = 200000; // p: parent, s: suffix link
string a; // edge p[v] -> v, contains a[l[v]..r[v]-1]
int t[N][64], l[N], r[N], p[N], s[N], tv, tp, ts, la;

void ukkadd(int c) {
	if (r[tv] <= tp) {
		if (t[tv][c] == -1) {
			t[tv][c]=ts; l[ts]=la; p[ts++]=tv;
			tv=s[tv]; tp=r[tv]; ukkadd(c); return;
		}
		tv=t[tv][c]; tp=l[tv];
	}

	if (tp == -1 || c == a[tp]-64) { tp++; return; }

	l[ts+1]=la; p[ts+1]=ts;
	l[ts]=l[tv]; r[ts]=tp; p[ts]=p[tv];
	t[ts][c]=ts+1; t[ts][a[tp]-64]=tv;
	l[tv]=tp; p[tv]=ts; t[p[ts]][a[l[ts]]-64]=ts;
	tv=s[p[ts]]; tp=l[ts];
	while (tp < r[ts])
		tv = t[tv][a[tp]-64], tp += r[tv] - l[tv];
	if (tp == r[ts]) s[ts]=tv;
	else s[ts]=ts+2;
	tp = r[tv] - (tp - r[ts]); ts += 2; ukkadd(c);
}

void build() {
	memset(t, -1, sizeof t);
	fill_n(t[1], 64, 0); fill_n(r, N, sz(a));
	l[0]=l[1]=-1; la=tv=tp=r[0]=r[1]=0; s[0]=1; ts=2;
	for (; la < sz(a); la++) ukkadd(a[la] - 64);
}

bool has_substr(const string &S) { // O(|S|)
	int v = 0, it = 0, n = sz(S);
	while (it < n) {
		int c = S[it++] - 64;
		if ((v = t[v][c]) < 0) return 0;
		for (int i = l[v]; it < n && ++i < r[v]; )
			if (S[it++] != a[i]) return 0;
	}
	return 1;
}
