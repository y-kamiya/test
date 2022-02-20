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


ll X;

void _main() {
    cin >> X;

    if (-10 < X && X < 10) {
        cout << floor((double)X / 10) << endl;
        return;
    }

    string s = to_string(X);
    int size = s.size();
    if (s[0] == '-' && s[size-1] != '0') {
        s.erase(s.end()-1);
        ll a = stoll(s);
        cout << a - 1 << endl;
        return;
    }

    s.erase(s.end()-1);
    cout << s << endl;
}

int main() {
    _main();
    return 0;
}

// AC 21:19

