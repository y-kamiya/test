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


ll dfs(const vector<int> &a, vector<vector<ll>> &dp, int first, int end, int p) {
    if (dp[first][end]) return dp[first][end];

    int sign = p ? -1 : 1;
    if (first == end) return dp[first][end] = a[first] * sign;

    auto f = dfs(a, dp, first+1, end, 1-p) + a[first] * sign;
    auto e = dfs(a, dp, first, end-1, 1-p) + a[end] * sign;

    DEBUG("first, end, p:", first, end, p, f, e);
    if (p) return dp[first][end] = min(f, e);
    return dp[first][end] = max(f, e);
}

void _main() {
    int N;
    cin >> N;

    vector<int> a(N);
    REP(i, N) cin >> a[i];

    vector<vector<ll>> dp(N, vector(N, 0LL));

    dfs(a, dp, 0, N-1, 0);

    ll ans = dp[0][N-1];
    cout << ans << endl;

}

int main() {
    _main();
    return 0;
}

