int dp[MAX_SIZE][MAX_SIZE]; // DP problem

int levDist(const string &w1, const string &w2) {
	int n1 = w1.size(), n2 = w2.size();
	for (int i = 0; i <= n1; i++) dp[i][0] = i; // removal
	for (int j = 0; j <= n2; j++) dp[0][j] = j; // insertion
	for (int i = 1; i <= n1; i++)
		for (int j = 1; j <= n2; j++)
			dp[i][j] = min(
				1 + min(dp[i - 1][j], dp[i][j - 1]),
				dp[i - 1][j - 1] + (w1[i - 1] != w2[j - 1])
			);
	return dp[n1][n2];
}
