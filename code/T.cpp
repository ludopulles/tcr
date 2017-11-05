#include<bits/stdc++.h>
using namespace std;

// BBST + order statistics (if supported by judge)
// iterator find_by_order(int r) (zero based)
// int order_of_key(TK v)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class TK, class TM> using order_tree = tree<TK, TM, less<TK>, rb_tree_tag, tree_order_statistics_node_update>;
template<class TV> using order_set = order_tree<TV, null_type>;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i=(a);i!=(b); ++i)
#define all(v) (v).begin(), (v).end()
#define rs resize
#define DBG(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl

template<class T> using min_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> int size(const T &x) { return x.size(); } // copy the ampersand(&)!

const int INF = 2147483647;
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
