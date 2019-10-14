#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i=(a);i!=(b); ++i)
#define REP(i,n) rep(i,0,n)
#define all(v) (v).begin(), (v).end()
#define rs resize

#define INFTY (1LL<<61LL)

struct bi_graph {
	ll n, m;
	vvi adj;
	vi L, R, d, q;
	bi_graph( ll _n, ll _m ) : n(_n), m(_m),
		adj(n), L(n,-1), R(m,n), d(n+1), q(n) {}
	ll bfs() {
		ll l = 0, r = 0;
		rep(v,0,n)
			if( L[v] == -1 ) d[v] = 0, q[r++] = v;
			else d[v] = INFTY;
		d[n] = INFTY;
		while( l < r ) {
			ll v = q[l++];
			if( d[v] < d[n] )
				for( ll u : adj[v] ) if( d[R[u]] == INFTY )
					d[R[u]] = d[v]+1, q[r++] = R[u];
		}
		return d[n] != INFTY;
	}
	ll dfs( ll v ) {
		if( v != n ) {
			for( ll u : adj[v] )
				if( d[R[u]] == d[v] + 1 and dfs(R[u]) ) {
					R[u] = v; L[v] = u;
					return true;
			}
			d[v] = INFTY;
			return false;
		}
		return true;
	}
	ll maximum_matching() {
		ll s = 0;
		while( bfs() ) rep(i,0,n)
			s += L[i] == - 1 && dfs( i );
		return s;
	}
};

signed main() {
	ll cases; cin >> cases;
	rep(q,0,cases) {
		AdjList.clear();
	    int c, d, v, i, j;
	    cin >> c >> d >> v;

	    AdjList.resize(v);
	    match.assign(v,-1);
	    vis.assign(v, 0);
	    vector<pair<string, string> > voters(v);
	    for( i = 0 ; i < v ; i++){
	        cin >> voters[i].first;
	        cin >> voters[i].second;
	    }
	    for( i = 0 ; i < v ; i++){
	        for( j = 0 ; j < v ; j++){
	            if( i == j )
	                continue;
	            if( voters[i].first == voters[j].second || voters[j].first == voters[i].second){
	                if( voters[i].first[0] == 'C')
	                    AdjList[i].push_back(j);
	                else
	                    AdjList[j].push_back(i);
	            }
	        }
	    }
		ll c, d, v;
		cin >> c >> d >> v;
		bi_graph G( c, d );
		rep(i,0,v) {
			cin >> ws;
			char c1 = cin.get();
			ll d1, d2;
			cin >> d1 >> ws;
			char c2 = cin.get();
			cin >> d2;
			if( c1 == 'D' )
				swap( d1, d2 );
			G.adj[d1-1].pb(d2-1);
		}
		cout << ( c + d - G.maximum_matching() ) << endl;
	}
}



