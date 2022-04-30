#include <algorithm>
#include <bits/stdc++.h>
#include <iterator>
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

template<typename Head, typename... Tail> void print(Head h, Tail... t);
template<typename T, typename... Tail> void print(vector<T> vec, Tail... t);

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

static const ll INF = 1LL<<61;

ll dfs(vector<vector<ll>> &dp, const vector<ll> &a, int l, int r) {
    if (dp[l][r] != INF) return dp[l][r];
    if (r-l == 0) return 0;

    FOR(i, l, r)
    ll lvalue = dfs(dp, a, l+1, r) + a[l];
    ll rvalue = dfs(dp, a, l, r-1) + a[r];
    return dp[l][r] = min(lvalue, rvalue);
}

void _main() {
    int N;
    cin >> N;

    vector<ll> a(N);
    REP(i, N) cin >> a[i];

    vector<vector<ll>> dp(N, vector(N, INF));
    ll ans = dfs(dp, a, 0, N-1);

    cout << ans << endl;

    // vector<ll> b(N-1);
    // ll ans = 0;
    // while (a.size() > 1) {
    //     int size_a = a.size();
    //     b.resize(size_a-1);
    //     REP(i, size_a-1) {
    //         b[i] = a[i] + a[i+1];
    //     }
    //     DEBUG("before", a, b);
    //     auto it = min_element(ALL(b));
    //     ans += *it;
    //     auto index = distance(b.begin(), it);
    //     a[index] = *it;
    //     a.erase(a.begin() + index + 1);
    //     DEBUG("after", a, b);
    // }
    //
    // cout << ans << endl;
}

int main() {
    _main();
    _main();
    _main();
    _main();
    _main();
    return 0;
}

