#include <bits/stdc++.h>
#include <climits>
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

void print() { cout << endl; }
template<typename Head, typename... Tail>
void print(Head h, Tail... t) {
    cout << h << " "; print(t...);
}
template<typename T, typename... Tail>
void print(vector<T> vec, Tail... t) {
    cout << "[";
    for (const auto &e : vec) {
        cout << e << ", ";
    }
    cout << "] ";
    print(t...);
}
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

static const ll INF = 1ll<<61;

using P = pair<ll, ll>;
struct Edge {
    ll to, cost;
};
struct Graph {
    ll n;
    vector<vector<Edge>> edges;
    vector<ll> dist;

    Graph(ll size) {
        n = size;
        edges.resize(n);
        dist.resize(n, INF);
    }

    void add_edge(ll s, ll t, ll cost) {
        Edge e{t, cost};
        edges[s].push_back(e);
    }

    void dijkstra(ll s) {
        REP(i, n) dist[i] = INF;
        dist[s] = 0;

        priority_queue<P, vector<P>, greater<P>> que;
        que.push({0, s});

        while (!que.empty()) {
            P p = que.top();
            que.pop();

            auto cost = p.first;
            auto v = p.second;

            if (dist[v] < cost) continue;

            for (const auto &e : edges[v]) {
                DEBUG(v, e.to, e.cost, dist[e.to]);
                if (dist[e.to] > dist[v] + e.cost) {
                    DEBUG(dist[e.to], dist[v], e.cost);
                    dist[e.to] = dist[v] + e.cost;
                    que.push({e.cost, e.to});
                }
            }
        }

    }
};

void _main() {
    int V, E, r;
    cin >> V >> E >> r;

    Graph G(V);
    ll s, t, d;
    REP(i, E) {
        cin >> s >> t >> d;
        G.add_edge(s, t, d);
    }

    G.dijkstra(r);

    REP(i, V) {
        if (G.dist[i] == INF) cout << "INF" << endl;
        else cout << G.dist[i] << endl;
    }
}

int main() {
    _main();
    return 0;
}

