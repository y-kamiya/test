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
template<typename T, typename... Tail>
void print(vector<T> vec, Tail... t) {
    cout << "[";
    for (const auto &e : vec) {
        cout << e << ", ";
    }
    cout << "] ";
    print(t...);
}
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif


void _main() {
    int N;
    cin >> N;

    vector<int> h(N+1), a(N+1);
    FOR(i, 1, N+1) cin >> h[i];
    FOR(i, 1, N+1) cin >> a[i];

    vector<vector<ll>> dp(N+1, vector(N+1, 0ll));
    FOR(i, 0, N) {
        FOR(j, 1, N+1) {
            if (dp[i+1][j] < dp[i][j]) dp[i+1][j] = dp[i][j];
        }
        FOR(j, 1, h[i+1]+1) {
            dp[i+1][h[i+1]] = max(dp[i+1][h[i+1]], dp[i][j] + a[i+1]);
            DEBUG(i+1, j, h[i+1], a[i+1], dp[i+1][h[i+1]]);
        }
    }

    REP(i, N+1) {
        DEBUG(dp[i]);
    }

    ll ans = 0;
    REP(h, N+1) ans = max(ans, dp[N][h]);

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

