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



int n, k;

void _main() {
    cin >> n >> k;

    int a[n+1];
    a[0] = 0;
    FOR(i, 1, n+1) cin >> a[i];

    int b[n+1];
    b[0] = a[0];
    FOR(i, 1, n+1) {
        b[i] = b[i-1] + a[i];
    }

    int m = 0;
    REP(i, n-k+1) {
        m = max(m, b[i+k] - b[i]);
    }

    cout << m << endl;
}

int main() {
    _main();
    return 0;
}

