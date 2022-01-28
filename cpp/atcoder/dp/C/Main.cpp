#include <bits/stdc++.h>
#include <string>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl

int N;
int a[100005][3];

void _main() {
    cin >> N;
    REP(i, N) cin >> a[i][0] >> a[i][1] >> a[i][2];

    int dp[N+1][3]; // i日時点でjを選んだ場合の最大幸福度
    memset(dp, 0, sizeof(dp));

    FOR(i, 0, N) {
        FOR(j, 0, 3) {
            dp[i+1][j] = max(dp[i][(j+1)%3], dp[i][(j+2)%3]) + a[i][j];
        }
    }

    cout << max(max(dp[N][0], dp[N][1]), dp[N][2]) << endl;
}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

// WA 10min
// AC 30min(途中休憩含む)
// 幸福度が同じ場合に対処するためdpを二重配列としてそれぞれを選んだ場合として保持する
// という形に気づくのに時間がかかった(最初は単に配列で計算していた)
