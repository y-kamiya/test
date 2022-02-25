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

using Graph = vector<vector<int>>;
int xs[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int ys[8] = {1, 1, 0, -1, -1, -1, 0, 1};

void dfs(const Graph &G, int i, int j, vector<vector<bool>> &seen) {
    seen[i][j] = true;

    REP(k, 8) {
        int ny = i + ys[k];
        int nx = j + xs[k];
        if (ny < 0 || G.size() <= ny) continue;
        if (nx < 0 || G[0].size() <= nx) continue;
        if (seen[ny][nx]) continue;
        if (G[ny][nx] == 0) continue;
        dfs(G, ny, nx, seen);
    }
}

void _main() {
    int w, h;
    cin >> w >> h;

    if (w == 0 && h == 0) exit(0);

    Graph c(h, vector<int>(w));
    REP(i, h) REP(j, w) cin >> c[i][j];

    vector<vector<bool>> seen(h, vector<bool>(w, false));

    int count = 0;
    REP(i, h) REP(j, w) {
        if (c[i][j] == 0) continue;
        if (seen[i][j]) continue;
        dfs(c, i, j, seen);
        ++count;
    }

    cout << count << endl;
}

int main() {
    while (true) _main();
    return 0;
}

