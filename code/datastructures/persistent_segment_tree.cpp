int segcnt = 0;
struct segment {
	int l, r, lid, rid, sum;
} S[2000000];

int build(int l, int r) {
	if (l > r) return -1;
	int id = segcnt++;
	S[id].l = l;
	S[id].r = r;
	if (l == r) S[id].lid = -1, S[id].rid = -1;
	else {
		int m = (l + r) / 2;
		S[id].lid = build(l , m);
		S[id].rid = build(m + 1, r);
	}
	S[id].sum = 0;
	return id;
}
int update(int idx, int v, int id) {
	if (id == -1) return -1;
	if (idx < S[id].l || idx > S[id].r) return id;
	int nid = segcnt++;
	S[nid].l = S[id].l;
	S[nid].r = S[id].r;
	S[nid].lid = update(idx, v, S[id].lid);
	S[nid].rid = update(idx, v, S[id].rid);
	S[nid].sum = S[id].sum + v;
	return nid;
}
int query(int id, int l, int r) {
	if (r < S[id].l || S[id].r < l) return 0;
	if (l<=S[id].l && S[id].r<=r) return S[id].sum;
	return query(S[id].lid,l,r)+query(S[id].rid,l,r);
}
