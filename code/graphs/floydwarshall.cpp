int n = 100; ll d[MAXN][MAXN];
for (int i = 0; i < n; i++) fill_n(d[i], n, 1e18);
// set direct distances from i to j in d[i][j] (and d[j][i])
for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		for (int k = 0; k < n; k++)
			d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
