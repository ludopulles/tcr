int kmp(const string &word, const string &text) {
	int n = word.size();
	vi T(n + 1, 0);
	for (int i = 1, j = 0; i < n; ) {
		if (word[i] == word[j]) T[++i] = ++j; // match
		else if (j > 0) j = T[j]; // fallback
		else i++; // no match, keep zero
	}
	int matches = 0;
	for (int i = 0, j = 0; i < text.size(); ) {
		if (text[i] == word[j]) {
			i++;
			if (++j == n) // match at interval [i - n, i)
				matches++, j = T[j];
		} else if (j > 0) j = T[j];
		else i++;
	}
	return matches;
}
