#define RESIZE
#define SWP(x,y) tmp = x, x = y, y = tmp
struct int_less {
	int_less() { }
	bool operator ()(const int &a, const int &b) {
		return a < b;
	}
};
template <class Compare = int_less> struct heap {
	int cap, len, *q, *loc, tmp;
	Compare _cmp;
	inline bool cmp(int i, int j) {
		return _cmp(q[i], q[j]);
	}
	inline void swp(int i, int j) {
		SWP(q[i], q[j]), SWP(loc[q[i]], loc[q[j]]);
	}
	void swim(int i) {
		while (i > 0) {
			int p = (i - 1) / 2;
			if (!cmp(i, p)) break;
			swp(i, p), i = p;
		}
	}
	void sink(int i) {
		while (true) {
			int l = 2*i + 1, r = l + 1;
			if (l >= len) break;
			int m = r >= len || cmp(l, r) ? l : r;
			if (!cmp(m, i)) break;
			swp(m, i), i = m;
		}
	}
	heap(int C=128) : len(0), cap(C), _cmp(Compare()) {
		q = new int[C]; loc = new int[C];
		memset(loc, 255, cap << 2);
	}
	~heap() {
		delete[] q; delete[] loc;
	}
	void push(int n, bool fix = true) {
		if (cap == len || n >= cap) {
#ifdef RESIZE
			int newcap = 2 * cap;
			while (n >= newcap) newcap *= 2;
			int *newq = new int[newcap], *newloc = new int[newcap];
			REP(i,cap) newq[i] = q[i], newloc[i]=loc[i];
			memset(newloc+cap, 255, (newcap-cap) << 2);
			delete[] q, delete[] loc;
			loc = newloc, q = newq, cap = newcap;
#else
			assert(false);
#endif
		}
		assert(loc[n] == -1);
		loc[n] = len, q[len++] = n;
		if (fix) swim(len-1);
	}
	void pop(bool fix = true) {
		assert(len > 0);
		loc[q[0]] = -1, q[0] = q[--len], loc[q[0]]=0;
		if (fix) sink(0);
	}
	int top() { assert(len > 0); return q[0]; }
	void heapify() {
		for (int i = len - 1; i > 0; i--)
			if (cmp(i, (i-1)/2)) swp(i, (i-1)/2);
	}
	void update_key(int n) {
		assert(loc[n]!=-1); swim(loc[n]); sink(loc[n]);
	}
	bool empty() { return len == 0; }
	int size() { return len; }
	void clear() {
		len = 0; memset(loc, 255, cap << 2);
	}
};
