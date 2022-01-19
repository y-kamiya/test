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

int N;
int h[100005];
int dp[100005]; // 足場iに着くまでに支払うコストの最小値

int cost(int i, int j) {
    return abs(h[i] - h[j]);
}

int main() {
    cin >> N;
    REP(i, N) cin >> h[i];

    REP(i, N) dp[i] = INF;
    dp[0] = 0;
    dp[1] = cost(0, 1);

    FOR(i, 2, N) {
        dp[i] = min(dp[i-1] + cost(i, i-1), dp[i-2] + cost(i, i-2));
    }

    cout << dp[N-1] << endl;

    return 0;
}

// AC 9min
