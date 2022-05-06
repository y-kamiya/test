#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define FORR(i,a,b) for(int i=(a);i>=(b);--i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl
#define PRINT_DOUBLE(n, x) cout << std::fixed << std::setprecision(n) << x << endl;

void print() { cout << endl; }

template<typename Head, typename... Tail>
void print(Head h, Tail... t) {
    cout << h << " "; print(t...);
}
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif


static const ll INF = 1ll<<61;

ll op(const vector<int> &t, const vector<int> &y, int i, ll x) {
    if (t[i] == 1) return y[i];
    return x + y[i];
}

void _main() {
    int N, K;
    cin >> N >> K;

    vector<int> t(N+1), y(N+1);
    FOR(i, 1, N+1) cin >> t[i] >> y[i];
    t[0] = 1;
    y[0] = 0;

    vector<vector<ll>> dp(N+1, vector(K+1, 0ll));
    FOR(i, 1, N+1) {
        FOR(j, 0, K+1) {
            dp[i][j] = op(t, y, i, dp[i-1][j]);
            DEBUG(i, j, dp[i][j]);
            if (j>0) dp[i][j] = max(dp[i][j], dp[i-1][j-1]);
        }
    }

    ll ans = -INF;
    REP(i, K+1) ans = max(ans, dp[N][i]);

    cout << ans << endl;
}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

