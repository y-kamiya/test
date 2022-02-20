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


void _main() {
    int H, W;
    cin >> H >> W;

    vector<vector<int>> a(H, vector<int>(W));
    REP(i, H) REP(j, W) cin >> a[i][j];

    vector<vector<int>> s(H+1, vector<int>(W+1));
    REP(i, H+1) s[i][0] = 0;
    REP(j, W+1) s[0][j] = 0;

    REP(i, H) {
        REP(j, W) {
            s[i+1][j+1] = a[i][j] + s[i+1][j] + s[i][j+1] - s[i][j];
        }
    }

    int Q;
    cin >> Q;

    int t, b, l, r;
    REP(i, Q) {
        cin >> t >> b >> l >> r;
        cout << s[b][r] - s[b][l] - s[t][r] + s[t][l] << endl;
    }
}

int main() {
    _main();
    return 0;
}

