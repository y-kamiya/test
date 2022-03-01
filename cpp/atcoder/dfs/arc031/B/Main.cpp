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

static const int MAX = 10;

int xs[4] = {0, 1, 0, -1};
int ys[4] = {1, 0, -1, 0};

void dfs(const vector<string> &G, int i, int j, vector<vector<bool>> &seen) {
    seen[i][j] = true;

    REP(k, 4) {
        int y = i + ys[k];
        int x = j + xs[k];
        if (y < 0 || MAX <= y) continue;
        if (x < 0 || MAX <= x) continue;
        if (seen[y][x]) continue;
        if (G[y][x] == 'x') continue;
        dfs(G, y, x, seen);
    }
}

void _main() {
    vector<string> A(MAX);
    REP(i, MAX) cin >> A[i];

    REP(h, MAX) {
        REP(w, MAX) {
            vector<string> B(A);
            if (B[h][w] == 'o') continue;
            B[h][w] = 'o';

            vector<vector<bool>> seen(MAX, vector<bool>(MAX, false));

            int count = 0;
            REP(i, MAX) {
                REP(j, MAX) {
                    if (B[i][j] == 'x') continue;
                    if (seen[i][j]) continue;
                    dfs(B, i, j, seen);
                    ++count;
                }
            }
            if (count == 1) {
                YES(1);
                return;
            }
        }
    }
    YES(0);
}

int main() {
    _main();
    return 0;
}

