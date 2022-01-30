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

const int MOD = 1000000007;

const int MAX = 1005;
int H, W;
ll dp[MAX][MAX];


ll f(int h, int w) {
    if (dp[h][w] != -1) return dp[h][w];

    ll n = f(h-1, w) + f(h, w-1);
    n %= MOD;
    dp[h][w] = n;
    // cout << h << w << ": " << dp[h][w] << endl;
    return n;
}

void _main() {
    cin >> H >> W;

    char a[H+1][W+1];
    FOR(i, 1, H+1) FOR(j, 1, W+1) cin >> a[i][j];
    REP(i, H+1) a[i][0] = '#';
    REP(j, W+1) a[0][j] = '#';

    memset(dp, -1, sizeof(dp));
    dp[1][1] = 1;
    FOR(i, 0, H+1) FOR(j, 0, W+1) {
        if (a[i][j] == '#') dp[i][j] = 0;
    }

    f(H, W);

    // REP(i, H+1) {
    //     REP(j, W+1) {
    //         cout << dp[i][j];
    //     }
    //     cout << endl;
    // }
    cout << dp[H][W] << endl;
}

int main() {
    _main();
    _main();
    _main();
    _main();
    return 0;
}

// AC 55min
// 2重配列を関数の引数にしようとして調査に時間がかかった
//  サイズが定数値でないと定義できないため今回のケースではだめだった
//  vectorを使う方法もあるがアクセス方法が変わるため面倒
// aとdpのindexをちゃんとあわせられておらずデバッグが必要だった
