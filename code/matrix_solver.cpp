typedef double NUM;
const int MAXROWS = 200, MAXCOLS = 200;
const NUM EPS = 1e-5;

// F2: bitset<MAXCOLS+1> mat[MAXROWS]; bitset<MAXROWS> vals;
NUM mat[MAXROWS][MAXCOLS + 1], vals[MAXCOLS]; bool hasval[MAXCOLS];
bool is0(NUM a) { return -EPS < a && a < EPS; }

// finds x such that Ax = b
// A_ij is mat[i][j], b_i is mat[i][m]
int solvemat(int n, int m) {
	// F2: vals.reset();
	int pr = 0, pc = 0;
	while (pc < m) {
		int r = pr, c;
		while (r < n && is0(mat[r][pc])) r++;
		if (r == n) { pc++; continue; }

		// F2: mat[pr] ^= mat[r]; mat[r] ^= mat[pr]; mat[pr] ^= mat[r];
		for (c = 0; c <= m; c++) swap(mat[pr][c], mat[r][c]);

		r = pr++; c = pc++;
		// F2: vals.set(pc, mat[pr][m]);
		NUM div = mat[r][c];
		for (int col = c; col <= m; col++) mat[r][col] /= div;
		REP(row, n) {
			if (row == r) continue;
			// F2: if (mat[row].test(c)) mat[row] ^= mat[r];
			NUM times = -mat[row][c];
			for (int col = c; col <= m; col++)
				mat[row][col] += times * mat[r][col];
		}
	} // now mat is in RREF
	
	for (int r = pr; r < n; r++)
		if (!is0(mat[r][m])) return 0;
	// F2: return 1;
	fill_n(hasval, n, false);
	for (int col = 0, row; col < m; col++) {
		hasval[col] = !is0(mat[row][col]);
		if (!hasval[col]) continue;
		for (int c = col + 1; c < m; c++) {
			if (!is0(mat[row][c])) hasval[col] = false;
		}
		if (hasval[col]) vals[col] = mat[row][n];
		row++;
	}
	REP(i, n) if (!hasval[i]) return 2;
	return 1;
}
