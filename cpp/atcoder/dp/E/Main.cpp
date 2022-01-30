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

static const int INF = 1<<29;

int N, W;
int w[105], v[105];
static const int V_MAX = 1000 * 100;

void _main() {
    cin >> N >> W;
    REP(i, N) cin >> w[i] >> v[i];

    ll dp[N+1][V_MAX+1];
    REP(i, N+1) REP(j, V_MAX+1) dp[i][j] = INF;
    REP(i, N) dp[i][0] = 0;
    // REP(j, V_MAX+1) dp[0][j] = 0; // 0番目の荷物だけで価値jとなる最小の重さなので0に初期化するのは間違い

    FOR(i, 0, N) {
        FOR(j, 0, V_MAX+1) {
            if (j - v[i] >= 0) dp[i+1][j] = min(dp[i][j], dp[i][j - v[i]] + w[i]); // minの第一引数のdpがi+1になっていたミス
            else dp[i+1][j] = min(dp[i][j], dp[i][j]);
        }
    }
    REP(j, 35) cout << j << "\t";
    cout << endl;
    REP(i, N) {
        REP(j, 35) {
            ll a = dp[i][j];
            if (dp[i][j] == 536870912) a = -1;
            cout << a << "\t";
        }
        cout << endl;
    }

    int ans = V_MAX;
    while (dp[N][ans] > W) --ans;
    cout << ans << endl;
}

int main() {
    _main();
    _main();
    cout << "=======================" << endl;
    _main();
    return 0;
}

// 解法を見る必要あった
// i番目までの荷物で価値jとする場合の最小の重さをdpとするのがキモだった
// 同じようなことは考えたが、最小ではなく最大で考えてしまい答えを導けず
