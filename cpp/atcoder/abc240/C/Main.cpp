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
    int N, X;
    cin >> N >> X;

    int a[N+1], b[N+1];
    FOR(i, 1, N+1) {
        cin >> a[i] >> b[i];
    }

    int dp[N+1][X+1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    FOR(i, 1, N+1) {
        FOR(j, 1, X+1) {
            if (j-a[i] >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j-a[i]]);
            if (j-b[i] >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j-b[i]]);
        }
    }

    // FOR(i, 0, N+1) {
    //     FOR(j, 0, X+1) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    Yes(dp[N][X]);
}

int main() {
    _main();
    // cout << "=============== " << endl;
    // _main();
    // cout << "=============== " << endl;
    // _main();
    return 0;
}

