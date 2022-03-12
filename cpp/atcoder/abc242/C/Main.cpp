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

static const ll MOD = 998244353;

ll dp[1000005][10];

void _main() {
    int N;
    cin >> N;

    memset(dp, 0, sizeof(dp));
    FOR(i, 1, 10) dp[1][i] = 1;

    FOR(i, 2, N+1) {
        // cout << dp[i][1] << endl;
        FOR(j, 1, 10) {
            // cout << dp[i][j] << endl;
            if (j == 1) dp[i][j] = (dp[i-1][1] + dp[i-1][2]) % MOD;
            else if (j == 9) dp[i][j] = (dp[i-1][8] + dp[i-1][9]) % MOD;
            else dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1]) % MOD;
        }
    }

    ll sum = 0;
    FOR(j, 1, 10) sum += dp[N][j] % MOD;
    cout << sum % MOD << endl;

    // ll count = 0;
    // FOR(j, 100, 1000) {
    //     string s = to_string(j);
    //     bool ok = true;
    //     REP(i, s.size()) {
    //         if (s[i] == '0') {
    //             ok = false;
    //             break;
    //         }
    //         if (i > 0 && abs(s[i]-s[i-1]) > 1) {
    //             ok = false;
    //             break;
    //         }
    //     }
    //     if (ok) {
    //         cout << j << endl;
    //         count++;
    //     }
    // }
    // cout << count << endl;
}

int main() {
    _main();
    return 0;
}

