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


int T;

void output(ll a, ll s) {
    if (a * 2 > s) {
        Yes(0);
        return;
    }

    ll b = s - 2 * a;
    if ((b & a) != 0) {
        Yes(0);
        return;
    }

    Yes(1);
}

void _main() {
    cin >> T;

    ll a[T], s[T];
    REP(i, T) cin >> a[i] >> s[i];

    REP(i, T) {
        output(a[i], s[i]);
    }
}

int main() {
    _main();
    return 0;
}

// 解説後に実装
