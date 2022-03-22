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
#define PRINt_DOUBLE(n, x) cout << std::fixed << std::setprecision(n) << x << endl;


void _main() {
    string s = "aaa";
    string t = "aaa";
    REP(i, 3) cin >> s[i];
    REP(i, 3) cin >> t[i];

    if (s == t) {
        Yes(1);
        return;
    }
    if (s[0] == t[0] || s[1] == t[1] || s[2] == t[2]) Yes(0);
    else Yes(1);
}

int main() {
    _main();
    return 0;
}

