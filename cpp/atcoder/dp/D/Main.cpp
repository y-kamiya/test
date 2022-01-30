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

int N, W;
int w[105];
int v[105];

void _main() {
    cin >> N >> W;
    REP(i, N) cin >> w[i] >> v[i];
    
    ll dp[N+1][W+1]; // i番目の荷物を重さjまで入れた場合の価値の最大値
    memset(dp, 0, sizeof(dp));

    FOR(i, 0, N) {
        FOR(j, 0, W+1) {
            dp[i+1][j] = max(dp[i][j], dp[i+1][j]);
            if (j - w[i] < 0) continue;
            dp[i+1][j] = max(dp[i][j-w[i]] + v[i], dp[i+1][j]);
        }
    }

    cout << dp[N][W] << endl;
}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

// AC 12min
