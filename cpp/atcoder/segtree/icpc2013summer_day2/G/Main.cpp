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
class SegmentTree {
    int n = 1;
    vector<T> tree;

    const T empty = 0;
    T op(T lhs, T rhs) const {
        return lhs + rhs;
    }
    void update_leaf(T &leaf, T val) {
        leaf = val;
    }

public:
    SegmentTree(int size) {
        while (n < size) n *= 2;
        tree.resize(2*n-1, empty);
    }

    void update(int x, T val) {
        x += (n-1);
        update_leaf(tree[x], val);
        while (x > 0) {
            x = (x-1)/2;
            tree[x] = op(tree[2*x+1], tree[2*x+2]);
        }
    }

    T query(int a, int b, int k=0, int l=0, int r=-1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return empty;
        if (a <= l && r <= b) return tree[k];

        int mid = (l+r)/2;
        auto vl = query(a, b, 2*k+1, l, mid);
        auto vr = query(a, b, 2*k+2, mid, r);
        return op(vl, vr);
    }
};


using u64 = std::uint_fast64_t;
template<u64 Mod> struct Modint {
    u64 val;
    constexpr Modint(const u64 x = 0) noexcept : val(x % Mod) {}
    constexpr u64 &value() noexcept { return val; }
    constexpr const u64 &value() const noexcept { return val; }
    constexpr Modint operator+(const Modint rhs) const noexcept {
        return Modint(*this) += rhs;
    }
    constexpr Modint operator-(const Modint rhs) const noexcept {
        return Modint(*this) -= rhs;
    }
    constexpr Modint operator*(const Modint rhs) const noexcept {
        return Modint(*this) *= rhs;
    }
    constexpr Modint operator/(const Modint rhs) const noexcept {
        return Modint(*this) /= rhs;
    }
    constexpr Modint &operator+=(const Modint rhs) noexcept {
        val += rhs.val;
        if (Mod <= val) val -= Mod;
        return *this;
    }
    constexpr Modint &operator-=(const Modint rhs) noexcept {
        if (val < rhs.val) val += Mod;
        val -= rhs.val;
        return *this;
    }
    constexpr Modint &operator*=(const Modint rhs) noexcept {
        val = val * rhs.val % Mod;
        return *this;
    }
    constexpr Modint &operator/=(Modint rhs) noexcept {
        ll a = rhs.val, b = Mod, u = 1, v = 0;
        while (b) {
            ll t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        val = val * u % Mod;
        if (u < 0) val += Mod;
        return *this;
    }
    constexpr bool operator == (const Modint& rhs) const noexcept {
        return this->val == rhs.val;
    }
    constexpr bool operator != (const Modint& rhs) const noexcept {
        return this->val != rhs.val;
    }
    friend constexpr ostream& operator << (ostream &os, const Modint<Mod>& x) noexcept {
        return os << x.value();
    }
};

static const int MOD = 1000000007;
using mint = Modint<MOD>;

void _main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> p(N+1), l(Q), r(Q);
    REP(i, N) cin >> p[i+1];
    REP(i, Q) cin >> l[i] >> r[i];

    SegmentTree<ll> seg(N);

    vector<int> x(N), y(N);
    vector<bool> done(Q);
    vector<mint> ret(Q, 0);
    REP(i, N) x[i] = i+1;

    DEBUG(x);

    while (!all_of(ALL(done), [](bool x) { return x; })) {
    // REP(_, 10) {
        REP(i, N) y[i] = p[x[i]];
        REP(i, N) {
            x[i] = y[i];
            seg.update(i, x[i]);
        }
        DEBUG(x);
        REP(i, Q) {
            if (done[i]) continue;
            ret[i] += seg.query(l[i]-1, r[i]);

            done[i] = true;
            FOR(j, l[i], r[i]+1) {
                if (x[j-1] != j) {
                    done[i] = false;
                    break;
                }
            }
        }
    }

    REP(i, Q) {
        cout << ret[i] << endl;
    }

}

int main() {
    _main();
    return 0;
}

