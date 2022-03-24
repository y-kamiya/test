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

static const int INF = INT_MAX / 2;

void _main() {
    int N;
    cin >> N;

    vector<int> h(N+1);
    FOR(i, 1, N+1) cin >> h[i];
    h[0] = 0;

    vector<int> dp(N+1, INF);
    dp[1] = 0;

    FOR(i, 1, N+1) {
        if (i-1 >= 1) dp[i] = min(dp[i], dp[i-1] + abs(h[i] - h[i-1]));
        if (i-2 >= 1) dp[i] = min(dp[i], dp[i-2] + abs(h[i] - h[i-2]));
    }

    cout << dp[N] << endl;
}

int main() {
    _main();
    return 0;
}

