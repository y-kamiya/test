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

int N;

void _main() {
    cin >> N;

    int A[N+1];
    FOR(i, 1, N+1) cin >> A[i];

    ll s[N+1];
    s[0] = 0;

    REP(i, N) {
        s[i+1] = s[i] + A[i+1];
    }

    // これではやはりTLE
    // ll count = 0;
    // FOR(i, 0, N) {
    //     FOR(j, i+1, N+1) {
    //         if (s[j] - s[i] == 0) ++count;
    //     }
    // }

    std::map<ll, ll> countMap;
    // s[0]も含めないと元々総和が0の部分列を取りそこねる
    FOR(i, 0, N+1) ++countMap[s[i]];

    ll res = 0;
    for (auto &p : countMap) {
        res += p.second * (p.second - 1) / 2;
    }

    cout << res << endl;
}

int main() {
    _main();
    return 0;
}

