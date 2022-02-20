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

static const int MAX = 100005;
vector<vector<int>> top(MAX, vector<int>());
int X[MAX];
Graph graph(MAX, vector<int>());

void dfs(int index, int p) {
    top[index].push_back(X[index]);

    // cout << index << ": ";
    // auto size = graph[index].size();
    // REP(i, size) cout << graph[index][i] << ", ";
    // cout << endl;

    if (graph[index].empty()) {
        return;
    }

    for (auto i : graph[index]) {
        if (i == p) continue;
        dfs(i, index);
        // top[index].insert(top[index].end(), top[i].begin(), top[i].end());
        for (auto v : top[i]) top[index].push_back(v);
    }
    sort(ALL(top[index]), greater<int>());

    top[index].resize(20);
}

void _main() {
    cin >> N >> Q;

    FOR(i, 1, N+1) cin >> X[i];

    int A, B;
    REP(i, N-1) {
        cin >> A >> B;
        // if (A < B) graph[A].push_back(B);
        // else graph[B].push_back(A);

        // 両方向にchild nodeを登録する必要があった
        // indexの小さい方が親という扱いや、A->BのみだとRE
        graph[A].push_back(B);
        graph[B].push_back(A);
        // cout << A << ", " << B << endl;
    }

    dfs(1, -1);

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
// おそらく入力に自己ノードへの連結があって無限ループによるRE
// また、ローカルで確保した大きな変数を渡していることによって再帰可能な枠が食いつぶされていた

