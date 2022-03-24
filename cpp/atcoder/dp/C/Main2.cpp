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
    int N;
    cin >> N;

    vector<int> a(N+1), b(N+1), c(N+1);
    FOR(i, 1, N+1) cin >> a[i] >> b[i] >> c[i];

    vector<vector<int>> dp(N+1, vector<int>(3, 0));
    REP(i, 3) dp[0][i] = 0;

    FOR(i, 1, N+1) {
        dp[i][0] = max(dp[i-1][1] + a[i], dp[i-1][2] + a[i]);
        dp[i][1] = max(dp[i-1][0] + b[i], dp[i-1][2] + b[i]);
        dp[i][2] = max(dp[i-1][0] + c[i], dp[i-1][1] + c[i]);
    }

    int ans = 0;
    REP(i, 3) ans = max(ans, dp[N][i]);

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

