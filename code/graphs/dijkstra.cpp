#define INFTY -1
vi dijkstra( vector<vii> G, ll s ) {
	vi d( G.size(), INFTY );
	priority_queue<ii,vector<ii>,greater<ii>> Q;
	Q.emplace(0,s);
	while(!Q.empty()){
		ll c = Q.top().x, a = Q.top().y;
		Q.pop();
		if(d[a] != INFTY)
			continue;
		d[a] = c;
		for(ii e : G[a])
			Q.emplace(d[a] + e.y, e.x);
	}
	return d;
}
