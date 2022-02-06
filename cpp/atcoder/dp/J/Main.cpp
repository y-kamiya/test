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

double f(double dp[][N_MAX+1][N_MAX+1], int i, int j, int k) {
    if (dp[i][j][k] != -1) return dp[i][j][k];

    double a = 1;
    if (i+j+k < N) {
        a -= (double)(N-i-j-k)/N;
    }

    double v = 1 / a;
    if (i > 0) v += f(dp, i-1, j+1, k) * (double)i/a/N;
    if (j > 0) v += f(dp, i, j-1, k+1) * (double)j/a/N;
    if (k > 0) v += f(dp, i, j, k-1) * (double)k/a/N;

    // cout << i << " " << j << " " << k << ": " << v << endl;
    dp[i][j][k] = v;
    return v;
}

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

    // cout << sum[3] << sum[2] << sum[1] << endl;
    // int dp[sum+1][N+1]; // 残りi個の寿司がj皿に残っている場合にたべきるまでの期待操作回数
    double dp[N_MAX+1][N_MAX+1][N_MAX+1]; // 残り3,2,1個の皿がそれぞれi, j, k枚から食べきるまでの期待操作回数
    REP(i, N_MAX+1) REP(j, N_MAX+1) REP(k, N_MAX+1) dp[i][j][k] = -1;
    dp[0][0][0] = 0;

    // ループではうまくいかない
    // FOR(i, 0, N_MAX+1) {
    //     FOR(j, 0, N_MAX+1) {
    //         FOR(k, 1, N_MAX+1) {
    //             if (0 <= k-1) dp[i][j][k] += dp[i][j][k-1] * (double)k/N;
    //             if (0 <= j-1) dp[i][j][k] += dp[i][j-1][k+1] * (double)j/N;
    //             if (0 <= i-1) dp[i][j][k] += dp[i-1][j+1][k] * (double)i/N;
    //             dp[i][j][k] += dp[i][j][k] * (double)(N-i-j-k)/N;
    //         }
    //     }
    // }
    // PRINT_DOUBLE(9, dp[sum[3]][sum[2]][sum[1]]);

    PRINT_DOUBLE(9, f(dp, sum[3], sum[2], sum[1]));
}

int main() {
    _main();
    _main();
    _main();
    _main();
    return 0;
}

// dpの定義は自分でできた
// ただし、0個の皿がえらばれる場合の考慮が漏れてたのと、再帰じゃないとうまくかけないのはわからず
