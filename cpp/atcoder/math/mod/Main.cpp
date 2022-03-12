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


ll modpow(ll a, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = (res * a) % mod;
        a *= a % mod;
        n >>= 1;
    }
    return res;
}

// modが素数の場合のみ有効
ll modinv_fermat(ll a, ll mod) {
    return modpow(a, mod-2, mod);
}

// modが素数でなくともOK
// ただし、逆元存在条件に注意
// - aとmodが互いに素
// - aがmodの倍数ではない
ll modinv(ll a, ll mod) {
    ll b = mod;
    ll u = 1;
    ll v = 0;
    while (b) {
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

void _main() {
    auto res = modpow(2, 4, 7);
    assert(res == 2);

    ll a = 423343;
    ll b = 74324;
    ll c = 13231;
    ll d = 8432455;
    ll mod = 1000000007;

    // https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a#8-modint
    // (a * b + c) / dの計算(modで割った余りで答える)
    auto ans = (a * b % mod + c) * modinv(d, mod) % mod;
    assert(ans == 79639022);
        
    cout << res << endl;
}

int main() {
    _main();
    return 0;
}

