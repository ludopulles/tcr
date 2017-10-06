const int MAXP = 100, MAXLEN = 200, SIGMA = 26, MAXTRIE = MAXP * MAXLEN;

int nP;
string P[MAXP], S;

int pnr[MAXTRIE], to[MAXTRIE][SIGMA], sLink[MAXTRIE], dLink[MAXTRIE], nnodes;

void ahoCorasick() {
	fill_n(pnr, MAXTRIE, -1);
	for (int i = 0; i < MAXTRIE; i++) fill_n(to[i], SIGMA, 0);
	fill_n(sLink, MAXTRIE, 0); fill_n(dLink, MAXTRIE, 0);
	nnodes = 1;
	// STEP 1: MAKE A TREE
	for (int i = 0; i < nP; i++) {
		int cur = 0;
		for (char c : P[i]) {
			int i = c - 'a';
			if (to[cur][i] == 0) to[cur][i] = nnodes++;
			cur = to[cur][i];
		}
		pnr[cur] = i;
	}
	// STEP 2: CREATE SUFFIX_LINKS AND DICT_LINKS
	queue<int> q; q.push(0);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int c = 0; c < SIGMA; c++) {
			if (to[cur][c]) {
				int sl = sLink[to[cur][c]] = cur == 0 ? 0 : to[sLink[cur]][c];
				// if all strings have equal length, remove this:
				dLink[to[cur][c]] = pnr[sl] >= 0 ? sl : dLink[sl];
				q.push(to[cur][c]);
			} else to[cur][c] = to[sLink[cur]][c];
		}
	}
	// STEP 3: TRAVERSE S
	for (int cur = 0, i = 0, n = S.size(); i < n; i++) {
		cur = to[cur][S[i] - 'a'];
		for (int hit = pnr[cur] >= 0 ? cur : dLink[cur]; hit; hit = dLink[hit]) {
			cerr << P[pnr[hit]] << " found at [" << (i + 1 - P[pnr[hit]].size()) << ", " << i << "]" << endl;
		}
	}
}
