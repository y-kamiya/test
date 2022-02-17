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

static const ll INF = 1LL<<60;

int V, E;

void _main() {
    cin >> V >> E;

    ll dp[V][V];
    REP(i, V) REP(j, V) dp[i][j] = INF;
    REP(i, V) dp[i][i] = 0;

    REP(i, E) {
        ll s, t, d;
        cin >> s >> t >> d;
        dp[s][t] = d;
    }

    REP(i, V) {
        REP(j, V) {
            REP(k, V) {
                if (dp[j][k] == INF && (dp[j][i] == INF || dp[i][k] == INF)) dp[j][k] = INF;
                else dp[j][k] = min(dp[j][k], dp[j][i] + dp[i][k]);
            }
        }
    }

    REP(j, V) {
        if (dp[j][j] < 0) {
            cout << "NEGATIVE CYCLE" << endl;
            return;
        }
    }

    REP(j, V) {
        REP(k, V) {
            if (dp[j][k] == INF) cout << "INF";
            else cout << dp[j][k];
            if (k != V-1) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    _main();
    return 0;
}

// dp[j][i]またはdp[i][k]がINFの場合にはINFを代入するように対応が必要
