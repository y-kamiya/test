#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl

static const int INF = 1<<29;

int N, K;
int h[100005];
int dp[100005]; // 足場iに着くまでに支払うコストの最小値

int cost(int i, int j) {
    return abs(h[i] - h[j]);
}

void _main() {
    cin >> N >> K;
    REP(i, N) cin >> h[i];

    REP(i, N) dp[i] = INF;
    dp[0] = 0;

    FOR(i, 1, N) {
        dp[i] = dp[i-1] + cost(i, i-1);
        FOR(k, 1, K+1) {
            if (i-k < 0) break;
            dp[i] = min(dp[i], dp[i-k] + cost(i, i-k));
        }
    }

    cout << dp[N-1] << endl;
}

int main() {
    _main();
    _main();

    return 0;
}

// WA 10min
// AC ? min
// 解説のコードとの違いはわかるが、どのように影響してWA-＞ACとなったか不明

