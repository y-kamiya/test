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

struct UnionFind {
    vector<ll> par;

    UnionFind(ll n) {
        par.assign(n, 0);
        REP(i, n) par[i] = i;
    }

    ll root(ll a) {
        if (a == par[a]) return a;
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


void _main() {
    string S;
    cin >> S;

    sort(ALL(S));

    cout << S << endl;
}

int main() {
    _main();
    return 0;
}

