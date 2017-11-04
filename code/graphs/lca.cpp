const int LOGSZ = 20, SZ = 1 << LOGSZ;
int P[SZ], BP[SZ][LOGSZ];

void initLCA() { // assert P[root] == root
	rep(i, 0, SZ) BP[i][0] = P[i];
	rep(j, 1, LOGSZ) rep(i, 0, SZ)
		BP[i][j] = BP[BP[i][j-1]][j-1];
}

int LCA(int a, int b) {
	if (H[a] > H[b]) swap(a, b);
	int dh = H[b] - H[a], j = 0;
	rep(i, 0, LOGSZ) if (dh & (1 << i)) b = BP[b][i];
	while (BP[a][j] != BP[b][j]) j++;
	while (--j >= 0) if (BP[a][j] != BP[b][j])
		a = BP[a][j], b = BP[b][j];
	return a == b ? a : P[a];
}
