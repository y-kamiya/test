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


string s, t;

void _main() {
    cin >> s >> t;

    int ns = (int)s.size();
    int nt = (int)t.size();

    int dp[ns+1][nt+1]; // sのi文字目, tのj文字目までを使った場合のLCS
    memset(dp, 0, sizeof(dp));

    FOR(i, 0, ns) {
        FOR(j, 0, nt) {
            if (s[i] == t[j]) dp[i+1][j+1] = dp[i][j] + 1;
            else dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
        }
    }

    int l = dp[ns][nt];
    int i = ns;
    int j = nt;
    string ss;
    while (l > 0) {
        if (s[i-1] == t[j-1]) {
            ss += s[i-1]; // sとtは0始まりのindexにしていたためi-1とする必要があることになかなか気づかず時間がかかった
            --i;
            --j;
            --l;
        } else if (dp[i][j] == dp[i-1][j]) --i;
        else --j;
    }

    std::reverse(ALL(ss));
    cout << ss << endl;
}

int main() {
    _main();
    _main();
    _main();
    _main();
    return 0;
}

// elseの部分を解釈してコードにできず
// ifの部分は一つずつ考えて理解し書き下した
