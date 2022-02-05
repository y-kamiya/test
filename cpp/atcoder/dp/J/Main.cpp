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



static const int N_MAX = 30;
int N;

void _main() {
    cin >> N;

    int a[N];
    REP(i, N) cin >> a[i];

    int sum[4];
    memset(sum, 0, sizeof(sum));
    REP(i, N) {
        FOR(j, 0, 4) {
            sum[j] += a[i] == j;
        }
    }

    cout << sum[3] << sum[2] << sum[1] << endl;
    // int dp[sum+1][N+1]; // 残りi個の寿司がj皿に残っている場合にたべきるまでの期待操作回数
    double dp[N_MAX+1][N_MAX+1][N_MAX+1]; // 残り3,2,1個の皿がそれぞれi, j, k枚から食べきるまでの期待操作回数
    memset(dp, 0, sizeof(dp));

    FOR(i, 0, N_MAX+1) {
        FOR(j, 0, N_MAX+1) {
            FOR(k, 1, N_MAX+1) {
                if (0 <= k-1) dp[i][j][k] += dp[i][j][k-1] + (double)N/k;
                if (0 <= j-1) dp[i][j][k] += dp[i][j-1][k+1] + (double)N/j;
                if (0 <= i-1) dp[i][j][k] += dp[i-1][j+1][k] + (double)N/i;
            }
        }
    }

    PRINT_DOUBLE(9, dp[sum[3]][sum[2]][sum[1]]);
}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

