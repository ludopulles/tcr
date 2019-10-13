int dp[MAX_SIZE][MAX_SIZE]; // DP problem

int levDist(const string &w1, const string &w2) {
	int n1 = sz(w1)+1, n2 = sz(w2)+1;
	REP(i, n1) dp[i][0] = i; // removal
	REP(j, n2) dp[0][j] = j; // insertion
	rep(i,1,n1) rep(j,1,n2)
		dp[i][j] = min(
			1 + min(dp[i-1][j], dp[i][j-1]),
			dp[i-1][j-1] + (w1[i-1] != w2[j-1])
		);
	return dp[n1][n2];
}
