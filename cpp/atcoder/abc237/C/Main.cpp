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



string S;

bool isOk(string s) {
    int ns = (int)s.size();

    REP(i, ns) {
        if (i >= ns-1-i) break;

        if (s[i] != s[ns-1-i]) {
            return false;
        }
    }
    return true;;
}

void _main() {
    // cout << "==================" << endl;
    cin >> S;

    int ns = (int)S.size();

    int x = 0;
    REP(i, ns) {
        if (S[i] == 'a') ++x;
        else break;
    }
    
    int y = 0;
    REP(i, ns) {
        if (S[ns-1-i] == 'a') ++y;
        else break;
    }

    if (x > y) {
        cout << "No" << endl;
        return;
    }

    S.insert(0, y-x, 'a');

    Yes(isOk(S));
}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

// TLE: 21:36
// 21:58頃一旦諦め(それまですべてTLE)
//
// eraseは後ろの文字を前に詰めていくためO(n)であることがTLEの原因
