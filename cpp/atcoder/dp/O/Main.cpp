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

#define bit(n,k) ((n>>k)&1)

void _main() {
    int N;
    cin >> N;

    vector<vector<int>> a(N, vector(N, 0));
    REP(i, N) REP(j, N) cin >> a[i][j];

    vector<mint> dp(1<<N, 0);
    dp[0] = 1;
    FOR(S, 1, 1<<N) {
       auto i = __builtin_popcount(S); 
       --i;
       REP(j, N) {
           if (bit(S,j) == 1 && a[i][j] == 1) {
               dp[S] += dp[S^(1<<j)];
           }
       }
    }

    cout << dp[(1<<N)-1] << endl;
}

int main() {
    _main();
    return 0;
}

