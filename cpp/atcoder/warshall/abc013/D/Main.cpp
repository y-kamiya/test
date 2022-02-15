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

static const int INF = 1<<29;


int N, M;

void _main() {
    cin >> N >> M;

    int dp[N][N];
    REP(i, N) REP(j, N) dp[i][j] = INF;
    REP(i, N) dp[i][i] = 0;

    int a, b, t;
    REP(i, M) {
        cin >> a >> b >> t;
        dp[a-1][b-1] = t;
        dp[b-1][a-1] = t;
    }

    REP(i, N) {
        REP(j, N) {
            REP(k, N) {
                dp[j][k] = min(dp[j][k], dp[j][i] + dp[i][k]);
            }
        }
    }

    int longest[N];
    memset(longest, 0, sizeof(longest));
    REP(i, N) REP(j, N) longest[i] = max(longest[i], dp[i][j]);

    int m = INF;
    REP(i, N) m = min(m, longest[i]);

    cout << m << endl;
}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

