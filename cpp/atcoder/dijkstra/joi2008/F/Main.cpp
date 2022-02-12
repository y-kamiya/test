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

            for (const auto &e : graph[v]) {
                auto d = dist[v] + e.cost;
                if (dist[e.to] > d) {
                    dist[e.to] = d;
                    que.emplace(d, e.to);
                }
            }
        }
    }

    void print() const {
        REP(i, num) {
            for (auto &e : graph[i]) {
                cout << i << " -> " << e.to << ": " << e.cost << endl;
            }
        }
    }
};

int n, k;

void _main() {
    cin >> n >> k;

    Graph g{n};
    int flag, s, t, cost;

    REP(i, k) {
        cin >> flag;
        if (flag == 1) {
            cin >> s >> t >> cost;
            g.addEdge(s-1, t-1, cost);
            g.addEdge(t-1, s-1, cost);
            continue;
        }

        cin >> s >> t;
        g.dijkstra(s-1);

        ll ans = g.dist[t-1];
        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << g.dist[t-1] << endl;
        }
    }
}

int main() {
    _main();
    return 0;
}

cf. https://nexusuica.hatenablog.jp/entry/2018/08/14/114524
cf. https://algo-logic.info/dijkstra/

