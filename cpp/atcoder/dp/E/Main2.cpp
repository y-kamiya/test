#include <bits/stdc++.h>
#include <climits>
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

static const ll INF = 1LL<<61;
static const int V_MAX = 100005;

void _main() {
    int N, W;
    cin >> N >> W;

    vector<int> w(N+1), v(N+1);
    FOR(i, 1, N+1) cin >> w[i] >> v[i];

    vector<vector<ll>> dp(N+1, vector<ll>(V_MAX, INF));
    // 価値が0になるときの最小の重さは0として初期化
    // dp[0][0]だけ初期化する場合は二重目のループを0から始める必要あり
    REP(i, N+1) dp[i][0] = 0;

    FOR(i, 1, N+1) {
        FOR(j, 1, V_MAX) {
            if (j < v[i]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = min(dp[i-1][j], dp[i-1][j-v[i]] + w[i]);
        }
    }

    // FOR(i, 1, N+1) {
    //     FOR(j, 1, 20) {
    //         cout << dp[i][j] << ", ";
    //     }
    //     cout << endl;
    // }

    ll ans = 0;
    FORR(i, V_MAX-1, 0) {
        if (dp[N][i] <= W) {
            ans = i;
            break;
        }
    }
    cout << ans << endl;

}

int main() {
    _main();
    return 0;
}

