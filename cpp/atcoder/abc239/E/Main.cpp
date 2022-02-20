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

int N,Q;
using Graph = vector<vector<int>>;

vector<int> dfs(int index, const Graph &graph, int X[], Graph &top) {
    vector<int> result;
    result.push_back(X[index]);

    // cout << index << ": ";
    // auto size = graph[index].size();
    // REP(i, size) cout << graph[index][i] << ", ";
    // cout << endl;

    if (graph[index].empty()) {
        top[index] = result;
        return top[index];
    }

    for (auto i : graph[index]) {
        auto vec = dfs(i, graph, X, top);
        if (vec.size() > 20) {
            result.insert(result.end(), vec.begin(), vec.begin() + 20);
        } else {
            result.insert(result.end(), vec.begin(), vec.end());
        }
    }
    sort(ALL(result), greater<int>());

    top[index].insert(top[index].begin(), result.begin(), result.begin() + min((int)result.size(), 20));
    return top[index];
}

void _main() {
    cin >> N >> Q;

    int X[N+1];
    FOR(i, 1, N+1) cin >> X[i];

    Graph graph;
    graph.resize(N+1);
    int A, B;
    REP(i, N-1) {
        cin >> A >> B;
        if (A < B) graph[A].push_back(B);
        else graph[B].push_back(A);
        // cout << A << ", " << B << endl;
    }

    vector<vector<int>> top;
    top.resize(N+1, {});

    dfs(1, graph, X, top);

    // FOR(i, 1, N+1) {
    //     auto size = top[i].size();
    //     cout << i << ": ";
    //     REP(j, size) cout << top[i][j] << ", ";
    //     cout << endl;
    // }

    int V, K;
    REP(i, Q) {
        cin >> V >> K;
        cout << top[V][K-1] << endl;
    }
}

int main() {
    _main();
    return 0;
}

// RE 23:08
//

