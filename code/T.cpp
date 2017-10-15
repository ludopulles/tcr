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

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i=(a);i!=(b); ++i)
#define all(v) (v).begin(), (v).end()
#define rs resize

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
template<class T> using min_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> int size(const T &x) { return x.size(); } // copy the ampersand(&)!

const int INF = 2147483647;
const ll LLINF = ~(1LL<<63); // = 9.223.372.036.854.775.807
const ld PI = acos(-1.0);

#ifdef LOCAL
#define DBG(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl
#else
#define DBG(x)
const bool LOCAL = false;
#endif

void Log() { if(LOCAL) cerr << "\n\n"; }
template<class T, class... S> void Log(T t, S... s) { if(LOCAL) cerr << t << "\t", Log(s...); }
// lambda-expression: [] (args) -> retType { body }

void run() {

}

int main() {
	ios_base::sync_with_stdio(false); // fast IO
	cin.tie(NULL); // fast IO
	(cout << fixed).precision(18); // adjust precision
	run();
	return 0;
}
