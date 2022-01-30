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


int H, W;

void _main() {
    cin >> H >> W;

    int A[H][W];
    REP(i, H) REP(j, W) cin >> A[i][j];

    REP(i, W) {
        REP(j, H) {
            cout << A[j][i] << " ";
        }
        cout << endl;
    }
}

int main() {
    _main();
    return 0;
}

// AC 21:18
