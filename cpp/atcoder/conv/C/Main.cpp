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


string S;
char c;

void _main() {
    cin >> S >> c;

    auto size = S.size();
    REP(i, size) {
        if (c < S[i]) {
            S.insert(S.begin()+i, c);
            cout << S << endl;
            return;
        }
    }

    S.insert(S.end(), c);
    cout << S << endl;
}

int main() {
    _main();
    _main();
    _main();
    _main();
    return 0;
}

