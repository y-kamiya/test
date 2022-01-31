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



int N;

void _main() {
    cin >> N;

    double p[N+1];
    FOR(i, 1, N+1) cin >> p[i];
    p[0] = 0;

    double dp[N+1][N+1]; // i番目のコインまで投げたとき、j枚表が出る確率
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    dp[1][0] = 1-p[0];

    FOR(i, 0, N+1) {
        FOR(j, 0, i) {
            dp[i+1][j+1] = dp[i][j] * p[i+1] + dp[i][j+1] * (1 - p[i+1]);
        }
    }

    double ans = 0;
    FOR(i, (N-1)/2 + 1, N+1) {
        ans += dp[N][i];
    }

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

