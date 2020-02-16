vi lis(vi arr) {
	vi seq, back(sz(arr)), ans;
	REP(i, sz(arr)) {
		int res = 0, lo = 1, hi = sz(seq);
		while (lo <= hi) {
			int mid = (lo+hi)/2;
			if (arr[seq[mid-1]] < arr[i]) res = mid, lo = mid + 1;
			else hi = mid - 1;
		}
		if (res < sz(seq)) seq[res] = i;
		else seq.pb(i);
		back[i] = res == 0 ? -1 : seq[res-1];
	}
	int at = seq.back();
	while (at != -1) ans.pb(at), at = back[at];
	reverse(all(ans));
	return ans;
}
