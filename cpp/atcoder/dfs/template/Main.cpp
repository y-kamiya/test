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


// 行きがけ順、帰りがけ順での順位を各頂点について出力
using Graph = vector<vector<int>>;

void dfs(const Graph &G, int v, vector<bool> &seen, vector<int> &first_order, int& first_ptr, vector<int> &last_order, int& last_ptr) {
    first_order[v] = first_ptr++;
    seen[v] = true;

    for (auto nv : G[v]) {
        if (seen[nv]) continue;
        dfs(G, nv, seen, first_order, first_ptr, last_order, last_ptr);
    }

    last_order[v] = last_ptr++;
}

void _main() {
    int N, M;
    cin >> N >> M;

    Graph G(N);
    REP(i, M) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vector<bool> seen(N, false);
    vector<int> first_order(N, 0);
    vector<int> last_order(N, 0);
    int first_ptr = 0;
    int last_ptr = 0;
    dfs(G, 0, seen, first_order, first_ptr, last_order, last_ptr);

    REP(v, N) {
        cout << v << ": " << first_order[v] << ", " << last_order[v] << endl;
    }
}

int main() {
    _main();
    return 0;
}

