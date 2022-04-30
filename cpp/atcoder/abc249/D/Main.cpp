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


void _main() {
    int N;
    cin >> N;

    vector<ll> A(N);
    REP(i, N) cin >> A[i];

    int MAX = 200000;
    vector<ll> count(MAX+1, 0);
    REP(i, N) {
        ++count[A[i]];
    }

    ll ans = 0;
    FOR(k, 1, MAX+1) {
        int m = MAX/k;
        FOR(j, 1, m+1) {
            ans += count[k] * count[j] * count[j*k];
        }
    }

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

