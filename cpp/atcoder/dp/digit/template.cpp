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

void print() { cout << endl; }
template<typename Head, typename... Tail>
void print(Head h, Tail... t) {
    cout << h << " "; print(t...);
}
template<typename T, typename... Tail>
void print(vector<T> vec, Tail... t) {
    cout << "[";
    for (const auto &e : vec) {
        cout << e << ", ";
    }
    cout << "] ";
    print(t...);
}
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

static const int MOD = 1e9+7;

// https://web.archive.org/web/20170508234139/https://pekempey.hatenablog.com/entry/2015/12/09/000603

// K以下の非負整数の総数
void _all() {
    string K;
    int D;
    cin >> K >> D;

    int n = K.size();
    vector<vector<ll>> dp(n+1, vector(2, 0ll));
    dp[0][0] = 1;

    // REP(i, n) {
    //     int lim = K[i]-'0';    
    //     REP(d, lim) {
    //         dp[i+1][1] += dp[i][0];
    //     }
    //     dp[i+1][0] += dp[i][0];
    //
    //     REP(d, 10) {
    //         dp[i+1][1] += dp[i][1];
    //     }
    // }
    //
    // REP(i, n+1) DEBUG(dp[i]);


    // 短い書き方
    REP(i, n) REP(j, 2) {
        int lim = j ? 9 : K[i]-'0';    
        REP(d, lim+1) {
            dp[i+1][j || d < lim] += dp[i][j];
        }
    }
    REP(i, n+1) DEBUG(dp[i]);
}


// K以下の非負整数のうち3のつく数の総数
void _with3() {
    string K;
    int D;
    cin >> K >> D;

    int n = K.size();
    vector<vector<vector<ll>>> dp(n+1, vector(2, vector(2, 0ll)));
    dp[0][0][0] = 1;

    REP(i, n) REP(k, 2) {
        int lim = K[i] - '0';
        REP(d, lim) {
            dp[i+1][1][k || d==3] += dp[i][0][k];
        }
        dp[i+1][0][k || lim==3] += dp[i][0][k];

        REP(d, 10) {
            dp[i+1][1][k || d==3] += dp[i][1][k];
        }
    }
    REP(i, n+1) REP(j, 2) DEBUG(dp[i][j]);
}

int main() {
    // _all();
    _with3();
    return 0;
}

