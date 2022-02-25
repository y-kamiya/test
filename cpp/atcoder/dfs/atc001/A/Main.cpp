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

int H, W;
using Graph = vector<vector<char>>;
using P = pair<int, int>;
P nextPos[4] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

void dfs(const Graph &G, const P &s, vector<vector<bool>> &seen) {
    seen[s.first][s.second] = true;

    for (auto &p : nextPos) {
        P np = {p.first + s.first, p.second + s.second};
        if (np.first < 0 || H <= np.first) continue;
        if (np.second < 0 || W <= np.second) continue;
        if (seen[np.first][np.second]) continue;
        if (G[np.first][np.second] == '#') continue;
        dfs(G, np, seen);
    }
}

void _main() {
    cin >> H >> W;

    Graph G(H, vector<char>(W));
    P start;
    P goal;
    REP(i, H) REP(j, W) {
        cin >> G[i][j];
        if (G[i][j] == 's') start = {i, j};
        if (G[i][j] == 'g') goal = {i, j};
    }

    vector<vector<bool>> seen(H, vector<bool>(W, false));

    dfs(G, start, seen);

    Yes(seen[goal.first][goal.second]);
}

int main() {
    _main();
    return 0;
}

