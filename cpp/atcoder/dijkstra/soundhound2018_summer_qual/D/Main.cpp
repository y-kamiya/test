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

static const ll INF = 1LL<<60;

struct Edge {
    ll to;
    ll cost;
};
using P = pair<ll, ll>;

struct Graph {
    ll num;
    vector<vector<Edge>> graph;
    vector<ll> dist;

    Graph(ll n) {
        num = n;
        graph.resize(n);
        dist.resize(n, INF);
    }

    void addEdge(ll s, ll t, ll cost) {
        Edge e{t, cost};
        graph[s].push_back(e);
    }

    void dijkstra(ll s) {
        REP(i, num) dist[i] = INF;
        dist[s] = 0;

        priority_queue<P, vector<P>, greater<P>> que;
        que.emplace(0, s);

        while (!que.empty()) {
            P p = que.top();
            que.pop();
            ll v = p.second;

            if (dist[v] < p.first) continue;

            for (auto &e : graph[v]) {
                ll d = dist[v] + e.cost;
                if (d < dist[e.to]) {
                    que.emplace(d, e.to);
                    dist[e.to] = d;
                }
            }
        }
    }
};

int n, m, s, t;

void _main() {
    cin >> n >> m >> s >> t;

    int u, v, a, b;
    Graph first{n}, second{n};

    REP(i, m) {
        cin >> u >> v >> a >> b;
        first.addEdge(u-1, v-1, a);
        first.addEdge(v-1, u-1, a);
        second.addEdge(u-1, v-1, b);
        second.addEdge(v-1, u-1, b);
    }

    first.dijkstra(s-1);
    second.dijkstra(t-1);

    vector<ll> outputs;
    ll costMin = INF;
    FORR(i, n-1, 0) {
        ll cost = first.dist[i] + second.dist[i];
        costMin = min(costMin, cost);
        outputs.push_back(costMin);
    }

    ll seed = pow(10, 15);
    FORR(i, n-1, 0) {
        cout << seed - outputs[i] << endl;
    }
}

int main() {
    _main();
    return 0;
}

