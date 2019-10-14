struct node {
	int l, r, x, lazy;
	node() {}
	node(int _l, int _r) : l(_l), r(_r), x(INT_MAX), lazy(0){}
	node(int _l, int _r, int _x) : node(_l,_r){x=_x;}
	node(node a,node b):node(a.l,b.r){x=min(a.x,b.x);}
	void update(int v) { x = v; }
	void range_update(int v) { lazy = v; }
	void apply() { x += lazy; lazy = 0; }
	void push(node &u) { u.lazy += lazy; }
};

struct segment_tree {
	int n;
	vector<node> arr;
	segment_tree() { }
	segment_tree(const vi &a) : n(sz(a)), arr(4*n) {
		mk(a,0,0,n-1); }
	node mk(const vi &a, int i, int l, int r) {
		int m = (l+r)/2;
		return arr[i] = l > r ? node(l,r) :
			l == r ? node(l,r,a[l]) :
			node(mk(a,2*i+1,l,m),mk(a,2*i+2,m+1,r));
	}
	node update(int at, ll v, int i=0) {
		propagate(i);
		int hl = arr[i].l, hr = arr[i].r;
		if (at < hl || hr < at) return arr[i];
		if (hl == at && at == hr) {
			arr[i].update(v); return arr[i]; }
		return arr[i] =
			node(update(at,v,2*i+1),update(at,v,2*i+2));
	}
	node query(int l, int r, int i=0) {
		propagate(i);
		int hl = arr[i].l, hr = arr[i].r;
		if (r < hl || hr < l) return node(hl,hr);
		if (l <= hl && hr <= r) return arr[i];
		return node(query(l,r,2*i+1),query(l,r,2*i+2));
	}
	node range_update(int l, int r, ll v, int i=0) {
		propagate(i);
		int hl = arr[i].l, hr = arr[i].r;
		if (r < hl || hr < l) return arr[i];
		if (l <= hl && hr <= r) {
			arr[i].range_update(v);
			propagate(i);
			return arr[i];
		}
		return arr[i] = node(range_update(l,r,v,2*i+1),
				range_update(l,r,v,2*i+2));
	}
	void propagate(int i) {
		if (arr[i].l < arr[i].r) {
			arr[i].push(arr[2*i+1]);
			arr[i].push(arr[2*i+2]);
		}
		arr[i].apply();
	}
};
