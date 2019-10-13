int dp[STR_SIZE][STR_SIZE]; // DP problem

int lcs(const string &w1, const string &w2) {
	int n1 = w1.size(), n2 = w2.size();
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (i == 0 || j == 0) dp[i][j] = 0;
			else if (w1[i-1] == w2[j-1])
				dp[i][j] = dp[i-1][j-1]+1;
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	return dp[n1][n2];
}

// backtrace
string getLCS(const string &w1, const string &w2) {
	int i = w1.size(), j = w2.size(); string ret = "";
	while (i > 0 && j > 0) {
		if (w1[i - 1] == w2[j - 1]) ret += w1[--i], j--;
		else if (dp[i][j - 1] > dp[i - 1][j]) j--;
		else i--;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}
