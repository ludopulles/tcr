typedef pair<ii, int> tii;
const int maxlogn = 17, maxn = 1 << maxlogn;

int p[maxlogn + 1][maxn]; tii L[maxn];

int suffixArray(string S) {
	int N = S.size(), stp = 1, cnt = 1;
	REP(i, N) p[0][i] = S[i];
	for (; cnt < N; stp++, cnt <<= 1) {
		REP(i, N)
			L[i] = tii(ii(p[stp-1][i], i + cnt < N ? p[stp-1][i + cnt] : -1), i);
		sort(L, L + N);
		REP(i, N)
			p[stp][L[i].y] = i > 0 && L[i].x == L[i-1].x ? p[stp][L[i-1].y] : i;
	}
	return stp - 1; // result is in p[stp - 1][0 .. (N - 1)]
}

