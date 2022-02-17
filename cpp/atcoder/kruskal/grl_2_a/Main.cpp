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

ll V, E;

ll root(ll a, ll par[]) {
    if (par[a] == a) return a;
    return par[a] = root(par[a], par);
}

void unite(ll a, ll b, ll par[]) {
    ll x = root(a, par);
    ll y = root(b, par);
    if (x != y) par[x] = y;
}

bool same(ll a, ll b, ll par[]) {
    return root(a, par) == root(b, par);
}

using P = pair<ll, pair<ll, ll>>;

void _main() {
    cin >> V >> E;

    ll par[V];
    REP(i, V) par[i] = i;

    priority_queue<P, vector<P>, greater<P>> que;
    REP(i, E) {
        ll s, t, d;
        cin >> s >> t >> d;
        que.emplace(d, pair<ll, ll>{s, t});
    }

    ll ans = 0;
    while (!que.empty()) {
        P p = que.top();
        que.pop();

        ll cost = p.first;
        ll s = p.second.first;
        ll t = p.second.second;

        if (same(s, t, par)) continue;

        unite(s, t, par);
        ans += cost;
    }

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

