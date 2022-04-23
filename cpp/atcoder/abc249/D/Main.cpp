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
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif


void _main() {
    int N;
    cin >> N;

    vector<ll> A(N);
    REP(i, N) cin >> A[i];

    vector<ll> dp(N, 0LL);
    if (A[0] == 1) dp[0] = 1;
    else dp[0] = 0;

    vector<int> count(200005, 0);
    ++count[A[0]];

    FOR(i, 0, N-1) {
        dp[i+1] = dp[i];
        REP(j, i) {
            ll tgt = A[i] * A[j];
            if (count[tgt] == 0) continue;

            if (A[i] == 1 && A[j] == 1) dp[i+1] += 3 * count[tgt] * (count[tgt]-1);
            else dp[i+1] += count[tgt] * 2;
        }
        DEBUG(i+1, dp[i+1]);
        ++count[A[i+1]];
    }

    cout << dp[N-1] << endl;
}

int main() {
    _main();
    return 0;
}

