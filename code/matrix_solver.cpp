typedef double NUM;
const int ROWS = 200, COLS = 200;
const NUM EPS = 1e-5;

// F2: bitset<COLS+1> M[ROWS]; bitset<ROWS> vals;
NUM M[ROWS][COLS + 1], vals[COLS];
bool hasval[COLS];

bool is0(NUM a) { return -EPS < a && a < EPS; }

// finds x such that Ax = b
// A_ij is M[i][j], b_i is M[i][m]
int solveM(int n, int m) {
	// F2: vals.reset();
	int pr = 0, pc = 0;
	while (pc < m) {
		int r = pr, c;
		while (r < n && is0(M[r][pc])) r++;
		if (r == n) { pc++; continue; }

		// F2: M[pr]^=M[r]; M[r]^=M[pr]; M[pr]^=M[r];
		for (c = 0; c <= m; c++)
			swap(M[pr][c], M[r][c]);

		r = pr++; c = pc++;
		// F2: vals.set(pc, M[pr][m]);
		NUM div = M[r][c];
		for (int col = c; col <= m; col++)
			M[r][col] /= div;
		REP(row, n) {
			if (row == r) continue;
			// F2: if (M[row].test(c)) M[row] ^= M[r];
			NUM times = -M[row][c];
			for (int col = c; col <= m; col++)
				M[row][col] += times * M[r][col];
		}
	} // now M is in RREF
	
	for (int r = pr; r < n; r++)
		if (!is0(M[r][m])) return 0;
	// F2: return 1;
	fill_n(hasval, n, false);
	for (int col = 0, row; col < m; col++) {
		hasval[col] = !is0(M[row][col]);
		if (!hasval[col]) continue;
		for (int c = col + 1; c < m; c++) {
			if (!is0(M[row][c])) hasval[col] = false;
		}
		if (hasval[col]) vals[col] = M[row][m];
		row++;
	}
	REP(i, n) if (!hasval[i]) return 2;
	return 1;
}
