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


struct UnionFind {
    vector<int> p;

    UnionFind(int size) {
        p.resize(size);
        REP(i, size) p[i] = i;
    }

    int root(int a) {
        if (a == p[a]) return a;
        return p[a] = root(p[a]);
    }

    bool same(int a, int b) {
        auto x = root(a);
        auto y = root(b);
        if (x == y) return true;
        return false;
    }

    void merge(int a, int b) {
        auto x = root(a);
        auto y = root(b);
        if (x == y) return;
        p[x] = y;
    }
};

using Edge = pair<int, pair<int, int>>;

void _main() {
    int V, E;
    cin >> V >> E;

    UnionFind uf(V);
    priority_queue<Edge, vector<Edge>, greater<Edge>> que;
    REP(i, E) {
        int s, t, w;
        cin >> s >> t >> w;
        Edge e = {w, {s, t}};
        que.push(e);
    }

    int sum = 0;
    while (!que.empty()) {
        Edge e = que.top();
        que.pop();
        auto w = e.first;
        auto s = e.second.first;
        auto t = e.second.second;

        if (uf.same(s, t)) continue;
        uf.merge(s, t);
        sum += w;
    }

    cout << sum << endl;
    
}

int main() {
    _main();
    return 0;
}

