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
    dp[1][0] = 1-p[1];

    FOR(i, 0, N) {
        dp[i+1][0] = dp[i][0] * (1 - p[i+1]);
        // cout << i+1 << "," << 0 << "  " << dp[i+1][0] << endl;
        FOR(j, 0, i+1) {
            dp[i+1][j+1] = dp[i][j] * p[i+1] + dp[i][j+1] * (1 - p[i+1]);
            // cout << i+1 << "," << j+1 << "  " << dp[i+1][j+1] << endl;
        }
    }

    double ans = 0;
    FOR(i, (N-1)/2 + 1, N+1) {
        ans += dp[N][i];
    }

    cout << std::fixed << std::setprecision(9) << ans << endl;
}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

// 解法を見てdpの定義の形を知ってから実装
// dp[i+1][0]の計算をしていなくて結果が合わなかった
// 桁数の9桁の指定も必須
