#include <bits/stdc++.h>
#include <functional>
#include <queue>
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


/*
 * 最小全域木で解けるかと思ったが違った
struct UnionFind {
    vector<ll> par;

    UnionFind(ll n) {
        par.resize(n);
        REP(i, n) par[i] = i;
    }

    ll root(ll a) {
        if (par[a] == a) return a;
        return par[a] = root(par[a]);
    }

    bool same(ll a, ll b) {
        return root(a) == root(b);
    }

    void merge(ll a, ll b) {
        ll x = root(a);
        ll y = root(b);
        if (x != y) par[x] = y;
    }
};

using P = pair<ll, pair<ll, ll>>;

void _main() {
    int N, M;
    cin >> N >> M;

    priority_queue<P, vector<P>, greater<P>> que;
    ll a, b, c;
    REP(i, M) {
        cin >> a >> b >> c;
        --a; --b;
        que.push({c, {a, b}});
    }

    UnionFind uf(N);
    int count = 0;
    while (!que.empty()) {
        P p = que.top();
        que.pop();

        ll a = p.second.first;
        ll b = p.second.second;

        if (uf.same(a, b)) {
            // cout << "drop:  " << a+1 << ", " << b+1 << ", " << p.first << endl;
            ++count;
            continue;
        }

        // cout << "merge: " << a+1 << ", " << b+1 << ", " << p.first << endl;
        uf.merge(a, b);
    }

    cout << count << endl;
}
*/

struct Edge {
    int s, t, cost;
};
static const int INF = INT_MAX/2;

void _main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges(M);
    int a, b, c;
    REP(i, M) {
        cin >> a >> b >> c;
        --a; --b;
        edges[i] = {a, b, c};
    }

    vector<vector<int>> dp(N, vector<int>(N));
    REP(i, N) REP(j, N) dp[i][j] = INF;
    // REP(i, N) dp[i][i] = 0;
    for (auto &e : edges) {
        dp[e.s][e.t] = e.cost;
        dp[e.t][e.s] = e.cost;
    }
    
    REP(k, N) {
        REP(i, N) {
            REP(j, N) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    int ans = 0;
    for (auto &e : edges) {
        REP(i, N) {
            if (dp[e.s][i] + dp[i][e.t] <= e.cost) {
                // cout << e.s+1 << ", " << i+1 << ", " << e.t+1 << ": " << dp[e.s][i] << " + " << dp[i][e.t] << endl;
                ++ans;
                break;
            }
        }
    }

    cout << ans << endl;

}

int main() {
    _main();
    return 0;
}

