void fht(vi &arr, bool inv=false, int l, int r) {
	if (l+1 == r) return;
	int k = (r-l)/2;
	if (!inv) fht(arr, inv, l, l+k), fht(arr, inv, l+k, r);
	rep(i,l,l+k) { int x = arr[i], y = arr[i+k];
		if (!inv) arr[i] = x-y, arr[i+k] = x+y;
		else arr[i] = (x+y)/2, arr[i+k] = (-x+y)/2; }
	if (inv) fht(arr, inv, l, l+k), fht(arr, inv, l+k, r); }
