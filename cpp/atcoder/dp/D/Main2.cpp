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


void _main() {
    int N, W;
    cin >> N >> W;

    vector<int> w(N+1), v(N+1);
    FOR(i, 1, N+1) cin >> w[i] >> v[i];

    vector<vector<ll>> dp(N+1, vector<ll>(W+1, 0));

    FOR(i, 1, N+1) {
        FOR(j, 1, W+1) {
            if (j < w[i]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i]);
        }
    }

    // REP(i, N+1) {
    //     REP(j, W+1) {
    //         cout << dp[i][j] << ", ";
    //     }
    //     cout << endl;
    // }

    cout << dp[N][W] << endl;

}

int main() {
    _main();
    // _main();
    // cout << "=========================" << endl;
    // _main();
    return 0;
}

