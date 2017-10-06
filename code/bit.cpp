int bit[MAXN + 1];

// arr[i] += v
void update(int i, int v) {
	while (i <= MAXN) bit[i] += v, i += i & -i;
}

// returns sum of arr[i], where i: [1, i]
int query(int i) {
	int v = 0; while (i) v += bit[i], i -= i & -i; return v;
}
