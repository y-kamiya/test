#include <bits/stdc++.h>
#include <unordered_map>
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
#define Accept(n) cout << ((n) ? "Accept" : "Reject"  ) << endl
#define PRINT_DOUBLE(n, x) cout << std::fixed << std::setprecision(n) << x << endl;


static const int LEN = 4;
string s;

void _main() {
    cin >> s;

    auto size = s.size();
    if (size != LEN) {
        Accept(0);
        return;
    }

    bool isSame = true;
    REP(i, LEN) {
        if (!isdigit(s[i])) {
            Accept(0);
            return;
        }
        if (i < size-1 && s[i] != s[i+1]) {
            isSame = false;
        }
    }

    if (isSame) {
        Accept(0);
        return;
    }

    Accept(1);
}

int main() {
    _main();
    _main();
    return 0;
}

