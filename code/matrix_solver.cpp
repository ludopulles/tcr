typedef double NUM;

#define MAXN 110
#define EPS 1e-5

NUM mat[MAXN][MAXN + 1], vals[MAXN];
bool hasval[MAXN];

bool is_zero(NUM a) { return -EPS < a && a < EPS; }
bool eq(NUM a, NUM b) { return is_zero(a - b); }

int solvemat(int n)
{
	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) cin >> mat[i][j];
	for (int i = 0; i < n; i++) cin >> mat[i][n];

	int pivrow = 0, pivcol = 0;
	while (pivcol < n) {
		int r = pivrow, c;
		while (r < n && is_zero(mat[r][pivcol])) r++;
		if (r == n) { pivcol++; continue; }

		for (c = 0; c <= n; c++) swap(mat[pivrow][c], mat[r][c]);

		r = pivrow++; c = pivcol++;
		NUM div = mat[r][c];
		for (int col = c; col <= n; col++) mat[r][col] /= div;
		for (int row = 0; row < n; row++) {
			if (row == r) continue;
			NUM times = -mat[row][c];
			for (int col = c; col <= n; col++) mat[row][col] += times * mat[r][col];
		}
	}
	// now mat is in RREF
	for (int r = pivrow; r < n; r++)
		if (!is_zero(mat[r][n])) return 0;

	fill_n(hasval, n, false);
	for (int col = 0, row; col < n; col++) {
		hasval[col] = !is_zero(mat[row][col]);
		if (!hasval[col]) continue;
		for (int c = col + 1; c < n; c++) {
			if (!is_zero(mat[row][c])) hasval[col] = false;
		}
		if (hasval[col]) vals[col] = mat[row][n];
		row++;
	}

	for (int i = 0; i < n; i++)
		if (!hasval[i]) return 2;
	return 1;
}
