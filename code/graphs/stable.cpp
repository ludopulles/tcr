// n = aantal mannen, m = aantal vrouwen
// voor een man i, is order[i] de prefere
vi stable(int n, int m, vvi order, vvi pref) {
	queue<int> q;
	REP(i, n) q.push(i);
	vi mas(m,-1), mak(n,-1), p(n,0);
	while (!q.empty()) {
		int k = q.front();
		q.pop();
		int s = order[k][p[k]], k2 = mas[s];
		if (mas[s] == -1) {
			mas[s] = k;
			mak[k] = s;
		} else if (pref[k][s] < pref[k2][s]) {
			mas[s] = k;
			mak[k] = s;
			mak[k2] = -1;
			q.push(k2);
		} else {
			q.push(k);
		}
		p[k]++;	
	}
	return mak;
}
