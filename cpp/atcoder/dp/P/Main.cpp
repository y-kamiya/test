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
using Graph = vector<vector<int>>;

mint dfs(const Graph &G, vector<vector<mint>> &dp, int v, int color, int p) {
    DEBUG(v+1, color, "start");
    if (dp[v][color] != 0) return dp[v][color];
    if (G[v].size() == 0) return dp[v][color] = 1;
    if (G[v].size() == 1 && G[v][0] == p) return dp[v][color] = 1;

    mint mul(1);
    for (auto nv : G[v]) {
        if (nv == p) continue;

        mint sum;
        sum += dfs(G, dp, nv, 1-color, v);
        if (color == 0) {
            sum += dfs(G, dp, nv, color, v);
        }
        mul *= sum;
    }

    DEBUG(v+1, color, mul);

    return dp[v][color] = mul;
}

void _main() {
    int N;
    cin >> N;

    Graph G(N);
    REP(i, N-1) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    vector<vector<mint>> dp(N, vector<mint>(2, 0));
    mint ans;
    REP(color, 2) {
        ans += dfs(G, dp, 0, color, -1);
    }

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

// 回答見ずにAC
// 80minくらい
// ある頂点v以下の塗り分け方をdp[v]とすればよいことに気づくまでに時間がかかった

