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

template<typename T>
class SegmentTreeLazy {
    ll n = 1;
    vector<ll> tree;
    vector<ll> lazy;

    T empty = INT_MAX;
    T op(T a, T b) {
        return min(a, b);
    }
    void _update(T &x, T val, T factor=1) {
        x = val;
    }
    void _update_child(T &x, T val) {
        x = val;
    }

public:
    SegmentTreeLazy(ll size) {
        while (n < size) n <<= 1;
        tree.resize(2*n-1, empty);
        lazy.resize(2*n-1, empty);
    }

    void eval(ll k, ll l, ll r) {
        if (lazy[k] == empty) return;

        _update(tree[k], lazy[k]);
        if (r-l > 1) {
            _update_child(lazy[2*k+1], lazy[k]);
            _update_child(lazy[2*k+2], lazy[k]);
        }

        lazy[k] = empty;
    }

    void update(ll a, ll b, ll x, ll k=0, ll l=0, ll r=-1) {
        if (r < 0) r = n;
        eval(k, l, r);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            _update(lazy[k], x, r-l);
            eval(k, l, r);
        } else {
            ll mid = (l+r)/2;
            update(a, b, x, 2*k+1, l, mid);
            update(a, b, x, 2*k+2, mid, r);
            tree[k] = op(tree[2*k+1], tree[2*k+2]);
        }
    }

    T query(ll a, ll b, ll k=0, ll l=0, ll r=-1) {
        if (r < 0) r = n;
        eval(k, l, r);
        if (b <= l || r <= a) return empty;
        if (a <= l && r <= b) return tree[k];

        ll mid = (l+r)/2;
        auto vl = query(a, b, 2*k+1, l, mid);
        auto vr = query(a, b, 2*k+2, mid, r);
        return op(vl, vr);
    }
};


void _main() {
    ll n, q;
    cin >> n >> q;

    SegmentTreeLazy<ll> seg(n);

    REP(i, q) {
        int c; cin >> c;
        if (c == 0) {
            ll s, t, x;
            cin >> s >> t >> x;
            seg.update(s, t+1, x);
        } else {
            ll s, t;
            cin >> s >> t;
            cout << seg.query(s, t+1) << endl;
        }
    }
}

int main() {
    _main();
    return 0;
}

