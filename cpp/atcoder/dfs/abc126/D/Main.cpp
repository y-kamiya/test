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


struct Edge {
    int to;
    int cost;
};
using Graph = vector<vector<Edge>>;

void dfs(const Graph &G, int v, vector<int> &color, int p = -1, int cur = 0) {
    color[v] = cur;

    for (auto &e : G[v]) {
        if (e.to == p) continue;
        if (color[e.to] != -1) continue;
        
        int next_color = cur;
        if (e.cost % 2 != 0) {
            next_color = 1 - cur;
        }
        dfs(G, e.to, color, v, next_color);
    }
}

void _main() {
    int N;
    cin >> N;

    Graph G(N, vector<Edge>());

    int u, v, w;
    REP(i, N-1) {
        cin >> u >> v >> w;
        --u, --v;
        Edge e1{v, w};
        G[u].push_back(e1);
        Edge e2{u, w};
        G[v].push_back(e2);
    }

    vector<int> color(N, -1);

    dfs(G, 0, color);

    REP(i, N) {
        cout << color[i] << endl;
    }
}

int main() {
    _main();
    // cout << "=================" << endl;
    // _main();
    return 0;
}

