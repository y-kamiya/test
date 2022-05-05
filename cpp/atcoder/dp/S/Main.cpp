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

static const int MOD = 1e9+7;

void _main() {
    string K;
    int D;
    cin >> K >> D;

    int n = K.size();
    vector<vector<vector<ll>>> dp(n+1, vector(2, vector(D, 0ll)));
    dp[0][0][0] = 1;

    REP(i, n) REP(j, 2) REP(k, D) {
        int lim = j ? 9 : K[i]-'0';    
        REP(d, lim+1) {
            dp[i+1][j || d<lim][(k+d)%D] += dp[i][j][k];
            dp[i+1][j || d<lim][(k+d)%D] %= MOD;
        }
    }

    REP(i, n+1) REP(j, 2) DEBUG(dp[i][j]);

    int ans = (dp[n][0][0] + dp[n][1][0] - 1 + MOD) % MOD;
    cout << ans << endl;

    // オーソドックスなDPにすると当然TLE
    // vector<vector<ll>> dp(n+1, vector(9*n+1, 0ll));
    // FOR(i, 1, 10) dp[1][i] = 1;
    //
    // DEBUG("n=", n);
    // FOR(i, 2, n+1) {
    //     FOR(j, 1, 9*n+1) {
    //         REP(k, 10) {
    //             if (j <= k) break;
    //             dp[i][j] += dp[i-1][j-k];
    //         }
    //     }
    // }
    //
    // REP(i, n+1) DEBUG(dp[i]);
    //
    // ll ans = 0;
    // FOR(i, 1, n+1) {
    //     REP(j, 9*n+1) {
    //         if (j % D == 0) ans = (ans + dp[i][j]) % MOD;
    //     }
    // }

    // cout << ans << endl;
}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

