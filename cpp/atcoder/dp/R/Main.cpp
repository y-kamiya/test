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

static const int MOD = 1e9+7;

void mul(vector<vector<ll>> &a, vector<vector<ll>> b, int mod) {
    int n = a.size();
    auto ret = vector(n, vector(n, 0ll));
    REP(i, n) {
        REP(j, n) {
            REP(k, n) {
                ret[i][j] += a[i][k] * b[k][j];
                ret[i][j] %= mod;
            }
        }
    }
    REP(i, n) REP(j, n) a[i][j] = ret[i][j];
}

void matrixpow(vector<vector<ll>> &A, ll k, int mod) {
    int n = A.size();
    auto ret = vector(n, vector(n, 0ll));
    REP(i, n) ret[i][i] = 1;

    while (k > 0) {
        if (k & 1) mul(ret, A, mod);
        mul(A, A, mod);
        k >>= 1;
    }

    REP(i, n) REP(j, n) A[i][j] = ret[i][j];
}

void _main() {
    ll N, K;
    cin >> N >> K;

    vector<vector<ll>> a(N, vector(N, 0ll));
    REP(i, N) REP(j, N) cin >> a[i][j];

    REP(i, N) DEBUG(a[i]);
    matrixpow(a, K, MOD);
    DEBUG("==============================");
    REP(i, N) DEBUG(a[i]);

    ll ans = 0;
    REP(i, N) REP(j, N) ans = (ans + a[i][j]) % MOD;

    cout << ans << endl;


    // vector<vector<vector<ll>>> dp(K, vector(N, vector(N, 0ll)));
    // REP(k, K) {
    //     REP(i, N) {
    //         REP(j, N) {
    //             REP(l, N) {
    //                 dp[k][i][j] = dp[k-1][i][l] * a[l][j];
    //             }
    //         }
    //     }
    // }
}

int main() {
    _main();
    return 0;
}

