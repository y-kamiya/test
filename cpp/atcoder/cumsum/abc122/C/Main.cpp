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


int N, Q;
string S;

void _main() {
    cin >> N >> Q;
    cin >> S;

    int a[N+1];
    a[0] = a[1] = 0;
    FOR(i, 2, N+1) {
        a[i] = a[i-1];
        if (S[i-2] == 'A' && S[i-1] == 'C') ++a[i];
        // cout << a[i] << endl;
    }

    int l, r;
    REP(i, Q) {
        cin >> l >> r;
        cout << a[r] - a[l] << endl;
    }
}

int main() {
    _main();
    return 0;
}

