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
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif


using u64 = std::uint_fast64_t;
struct Modint {
    static u64 mod;
    u64 val;
    Modint(const u64 x = 0) noexcept : val(x % mod) {}
    u64 &value() noexcept { return val; }
    const u64 &value() const noexcept { return val; }
    Modint operator+(const Modint rhs) const noexcept {
        return Modint(*this) += rhs;
    }
    Modint operator-(const Modint rhs) const noexcept {
        return Modint(*this) -= rhs;
    }
    Modint operator*(const Modint rhs) const noexcept {
        return Modint(*this) *= rhs;
    }
    Modint operator/(const Modint rhs) const noexcept {
        return Modint(*this) /= rhs;
    }
    Modint &operator+=(const Modint rhs) noexcept {
        val += rhs.val;
        if (mod <= val) val -= mod;
        return *this;
    }
    Modint &operator-=(const Modint rhs) noexcept {
        if (val < rhs.val) val += mod;
        val -= rhs.val;
        return *this;
    }
    Modint &operator*=(const Modint rhs) noexcept {
        val = val * rhs.val % mod;
        return *this;
    }
    Modint &operator/=(Modint rhs) noexcept {
        ll a = rhs.val, b = mod, u = 1, v = 0;
        while (b) {
            ll t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        val = val * u % mod;
        if (val < 0) val += mod;
        return *this;
    }
    bool operator == (const Modint& rhs) const noexcept {
        return this->val == rhs.val;
    }
    bool operator != (const Modint& rhs) const noexcept {
        return this->val != rhs.val;
    }
    friend ostream& operator << (ostream &os, const Modint& x) noexcept {
        return os << x.value();
    }
};
u64 Modint::mod;


void _main() {
    int N, P;
    cin >> N >> P;

    Modint::mod = P;

    if (N < 3) {
        cout << 0 << endl;
        return;
    }

    vector<vector<Modint>> comb(N+1, vector(N+1, Modint()));
    FOR(i, 0, N) {
        comb[i][0] = 1;
        comb[i][i] = 1;
    }
    FOR(i, 1, N+1) {
        FOR(j, 1, i) {
            comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
        }
    }


    Modint sum(0);

    FOR(n_char, 1, (N-1)/2+1) {
        Modint ans(26);
        REP(j, n_char-1) {
            ans *= Modint(25);
        }
        ans *= comb[N-1][n_char-1];
        DEBUG(comb[N-1][n_char-1]);

        DEBUG("n_char", n_char, ans);
        sum += ans;
    }

    cout << sum << endl;
}

int main() {
    _main();
    _main();
    DEBUG("===================");
    _main();
    _main();
    return 0;
}

