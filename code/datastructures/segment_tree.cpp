typedef /* Tree element */ S;
const int n = 1 << 20;
S t[2 * n];

// required axiom: associativity
S combine(S l, S r) { return l + r; } // sum segment tree
S combine(S l, S r) { return max(l, r); } // max segment tree

void build() {
	for (int i = n; --i; ) t[i] = combine(t[2 * i], t[2 * i + 1]);
}

// set value v on position i
void update(int i, S v) {
	for (t[i += n] = v; i /= 2; ) t[i] = combine(t[2 * i], t[2 * i + 1]);
}

// sum on interval [l, r)
S query(int l, int r) {
	S resL, resR;
	for (l += n, r += n; l < r; l /= 2, r /= 2) {
		if (l & 1) resL = combine(resL, t[l++]);
		if (r & 1) resR = combine(t[--r], resR);
	}
	return combine(resL, resR);
}
