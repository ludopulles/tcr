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
#define DBG(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl

template<class T> using min_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> int size(const T &x) { return x.size(); } // copy the ampersand(&)!

template<class T> ostream& operator<<(ostream& os,vector<T>& v) {
	os << "\n["; for( T& x : v ) os << x << ","; return os << "]";
}

const ll INF = 2147483647;
const ll LLINF = ~(1LL<<63); // = 9.223.372.036.854.775.807
const ld PI = acos(-1.0);

void run() {

}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	(cout << fixed).precision(18);
	run();
	return 0;
}
