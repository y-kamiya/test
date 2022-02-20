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
    int N;
    cin >> N;

    vector<vector<int>> D(N, vector<int>(N));
    REP(i, N) REP(j, N) cin >> D[i][j];

    int Q;
    cin >> Q;

    vector<int> P(Q);
    REP(i, Q) cin >> P[i];

    vector<vector<int>> s(N+1, vector<int>(N+1));
    REP(i, N+1) s[i][0] = 0;
    REP(i, N+1) s[0][i] = 0;

    REP(i, N) {
        REP(j, N) {
            s[i+1][j+1] = D[i][j] + s[i+1][j] + s[i][j+1] - s[i][j];
        }
    }

    REP(i, Q) {
        int res = 0;
        FOR(j, 1, P[i]+1) {
            int H = j;
            int W = min(P[i] / H, N);
            if (H > N) continue;
            
            // cout << "H: " << H << ", W: " << W << endl;
            FOR(t, 1, N+1) {
                FOR(l, 1, N+1) {
                    int b = t + H - 1;
                    int r = l + W - 1;
                    if (b > N || r > N) continue;
                    // cout << t << " " << l << " " << b << " " << r << endl;

                    res = max(res, s[b][r] - s[t-1][r] - s[b][l-1] + s[t-1][l-1]);;
                }
            }
        }
        cout << res << endl;
    }

}

int main() {
    _main();
    _main();
    return 0;
}

